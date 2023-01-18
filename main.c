/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corporan <corporan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:32:04 by lcorpora          #+#    #+#             */
/*   Updated: 2023/01/18 02:41:32 by corporan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_all_eat(t_stat *data)
{
	// pthread_mutex_lock(&(data->dead));
	data->all_ate = 1;
	// pthread_mutex_unlock(&(data->dead));
	return (1);
}

int	data_all_eat1(t_stat *data)
{
	if (check_nb_eat(data) == 1)
		mutex_all_eat(data);
	return (check_nb_eat(data));
}

int	check_nb_eat(t_stat *data)
{
	int	i;

	i = data->nb_philo - 1;
	pthread_mutex_lock(&(data->dead));
	if (data->philo_died == 1)
	{
		pthread_mutex_unlock(&(data->dead));
		return (1);
	}
	pthread_mutex_unlock(&(data->dead));
	if (data->m_eat == -1)
		return (0);
	i = data->nb_philo;
	while (--i >= 0)
	{
		// pthread_mutex_lock(&(data->philo[i].m_philo));
		if (data->philo[i].x_eat < data->m_eat)
		{
			// pthread_mutex_unlock(&(data->philo[i].m_philo));
			return (0);
		}
		// pthread_mutex_unlock(&(data->philo[i].m_philo));
	}
	mutex_all_eat(data);
	return (1);
}

int	do_pthread_odd(t_stat *data)
{
	int	i;
	pthread_t	*phi;

	i = 0;

	phi = malloc(sizeof(pthread_t) * data->nb_philo);
	data->time_start = time_phi();
	while (i < data->nb_philo)
	{
		data->philo[i].last_meal = time_phi();
		// if (data->philo[i].id % 2 == 0)
		// {
			if (pthread_create (&phi[i], 0,
					routine, &(data->philo[i])))
				return (ft_error("Error with creating a thread"), 0);
		// }
		i++;
	}
	// death_checker(data, data->philo);
	finish_all_mutex(data, phi);
	exit_mutex(data);
}

int	main(int ac, char **av)
{
	t_stat	data;

	if (ac != 5 && ac != 6)
	{
		ft_error("Invalid number of arguments\n");
		return (0);
	}
	if (check_args(av, ac))
		return (0);
	if (init_stat(av, &data) == 0)
	{
		ft_error("imposible to initialize data\n");
		return (0);
	}
	// while(1)
	// {
	// 	printf("here\n");
	// }
	// do_pthread(&data);
	do_pthread_odd(&data);
	return (1);
}
