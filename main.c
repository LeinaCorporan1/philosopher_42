/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:32:04 by lcorpora          #+#    #+#             */
/*   Updated: 2022/12/21 13:23:13 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_die_philo2(t_stat *data)
{
	int	dead;

	dead = -1;
	pthread_mutex_lock(&(data->dead));
	dead = data->philo_died;
	pthread_mutex_unlock(&(data->dead));
	if (dead == 1)//voir si je met superieur a 1 ou egal
		return (1);
	return (0);
}

int	mutex_dead(t_stat *data, t_philo *philo)
{
	print (time_phi(), data->philo, "died",data);
	pthread_mutex_lock(&(data -> dead));
	data -> philo_died = 1;
	pthread_mutex_unlock(&(data -> dead));
	return (1);
}

int	check_nb_eat(t_stat *data)
{
	int	i;
	
	i = data -> nb_philo - 1;
	if (data -> m_eat == -1)
		return (0);
	i = data -> nb_philo;
	while (--i >= 0)
	{
		pthread_mutex_lock(&(data -> must_eat[i]));
		if (data -> philo[i].x_eat < data->m_eat)
		{
			pthread_mutex_unlock(&(data->must_eat[i]));
			return (0);
		}
		pthread_mutex_unlock(&(data->must_eat[i]));
	}
	return (1);
}

int	mutex_all_eat(t_stat *data)
{
	pthread_mutex_lock(&(data->dead));
	data->all_ate = 1;
	pthread_mutex_unlock(&(data->dead));
	return (1);
}

int	data_all_eat1(t_stat *data)
{
	if (check_nb_eat(data) == 1)
		mutex_all_eat(data);
	return (check_nb_eat(data));
}

int	check_data_died(t_stat *data)
{
	int	retour;

	retour = 0;
	pthread_mutex_lock(&(data -> dead));
	retour = data ->philo_died;
	pthread_mutex_unlock(&(data -> dead));
	return (retour);
}

int	check_die_philo(t_stat *data)
{
	int	i;

	i = data -> nb_philo;
	while (--i > 0)
		if (data->philo[i].is_dead == 1)
			return (1);
	return (0);
}

void	death_checker(t_stat *data, t_philo *philo)
{
	int	i;

	while (check_nb_eat(data) == 0)
	{
		i = -1;
		while (++i < data -> nb_philo && (check_die_philo(data) == 0))
		{
			pthread_mutex_lock(&(data -> eating));
			if ((time_phi() - philo[i].last_meal) > data->die)
				mutex_dead(data, &philo[i]);
			pthread_mutex_unlock(&(data -> eating));
			usleep(100);
		}
		if (check_data_died(data) == 1)
		{
			finish_all_mutex(data, philo);
			exit_mutex(data);
			break ;
			// exit(1) ;
		}
			// break ;
		i = data_all_eat1(data);
	}
}

void	finish_all_mutex(t_stat *data, t_philo *philo)
{
	int	i;

	i = data -> nb_philo;
	while (--i >= 0)
	{
		pthread_join(philo[i].phi, NULL);
		pthread_mutex_destroy(&(philo[i].l_fork));
	}
}

void	exit_mutex(t_stat *data)
{
	int	i;

	i =data -> nb_philo;
	while (--i >= 0)
	{
		pthread_mutex_destroy(&(data->must_eat[i]));
	}
	i =data -> nb_philo;
	free (data ->must_eat);
}

int	do_pthread(t_stat *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = data -> philo;
	data -> time_start = time_phi();
	while (i < data -> nb_philo)
	{
		if (pthread_create(&(philo[i].phi), NULL,routine, &(philo[i])))
		{
			ft_error("Error with creating a thread");
			return (0);
		}
		pthread_mutex_lock(&(data->must_eat[i]));
		philo[i].last_meal = time_phi();
		pthread_mutex_unlock(&(data->must_eat[i]));
		i++;
	}
	death_checker( data, data->philo);
	finish_all_mutex(data, philo);
	exit_mutex(data);
	return (0);
}

size_t	ft_strlen(char *c)
{
	size_t	count;

	count = 0;
	while (*c)
	{	
		count++;
		c++;
	}
	return (count);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
	{
		// printf("this ine %c\n", c);	
		return (1);
	}
	return (0);
}

int	check_args(char **av, int ac)
{
	int i;
	int y;
	int rtn;

	i = 1;
	rtn = 0;
	printf("inside check_args ac = %d\n", ac);
	if (ac != 5 && ac != 6)
	{
		ft_error("Invalid number of arguments\n");
		return (1);
	}
	while(av[i])
	{
		if (ft_strlen(av[i]) > 10 || ft_atoi(av[i]) < 0 || ft_atoi(av[i]) > INT_MAX)
			rtn = 1;
		y = 0;
		while(av[i][y])
		{
			if (!ft_isdigit(av[i][y]))
				rtn = 1;
			// printf("ft_is digit i = [%d] y = [%d ] ==== [%c] = %d",i,y, av[i][y], rtn);
			if (rtn == 1)
			{
				ft_error("Invalid arguments\n");
				return (1);
			}
			y++;
		}
		i++;
	}
	return (0);
}

int main(int ac, char **av)
{
	t_stat data;

	if(check_args(av, ac))
		return (0);
	if (init_stat(av, &data) == 0)
		ft_error("imposible to initialize data\n");
	// if (init_philo(&philo ,&data))
	printf("done data nb_philo %lld\n", data.nb_philo);
	do_pthread(&data);
		return (1);
}
//je dois checker pk ca marche pas avec ./philo 4 2147483647 200 200 et aussi si il y a que 1
