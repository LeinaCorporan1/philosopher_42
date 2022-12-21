/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:49:56 by lcorpora          #+#    #+#             */
/*   Updated: 2022/12/21 17:25:36 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_phi(void *philosopher)
{
	t_philo		*philo;

	philo = (t_philo *)philosopher;
	print(0, philo, "has taken a fork", philo->data);
	ft_sleep(philo->data->die, philo->data);
	print(philo->data->die, philo, "died", philo->data);
	return (0);
}

void	eating(void *philosophers)
{
	t_stat	*data;
	t_philo	*philo;

	philo = (t_philo *)philosophers;
	data = philo->data;
	pthread_mutex_lock((philo->r_fork));
	print(time_phi(), philo, "has taken a fork", data);
	pthread_mutex_lock(&(philo->l_fork));
	print(time_phi(), philo, "has taken a fork", data);
	pthread_mutex_lock(&(data -> eating));
	print(time_phi(),philo, "is eating",data);
	pthread_mutex_lock(&(data->must_eat[philo->id -1]));
	philo -> last_meal = time_phi();
	pthread_mutex_unlock(&(data->must_eat[philo->id -1]));
	pthread_mutex_unlock(&(data->eating));
	ft_sleep(data->eat, data);
	pthread_mutex_lock(&(data->must_eat[philo->id -1]));
	philo->x_eat++;
	pthread_mutex_unlock(&(philo->l_fork));
		pthread_mutex_unlock((philo->r_fork));
	pthread_mutex_unlock(&(data->must_eat[philo->id -1]));
}

void	pair_eating(void *philosophers)
{
	t_stat	*data;
	t_philo *philo;

	philo = (t_philo *)philosophers;
	data = philo->data;
	if (philo->id % 2 != 0)
		pthread_mutex_lock(&(philo->l_fork));
	else
		pthread_mutex_lock((philo->r_fork));
	print(time_phi(),philo, "has taken a fork", data);
	if (philo->id % 2 != 0)
		pthread_mutex_lock((philo->r_fork));
	else
		pthread_mutex_lock(&(philo->l_fork));
	print(time_phi(),philo, "has taken a fork", data);
	// pthread_mutex_lock(&(data->eating));
	print(time_phi(),philo, "is eating", data);
	pthread_mutex_lock(&(data->must_eat[philo->id - 1]));
	philo -> last_meal = time_phi();
	pthread_mutex_unlock(&(data->must_eat[philo->id - 1]));
	// pthread_mutex_unlock(&(data->eating));
	ft_sleep(data->eat, data);
	pthread_mutex_lock(&(data->must_eat[philo->id - 1]));
	philo->x_eat++;
	pthread_mutex_unlock(&(data->must_eat[philo->id - 1]));
	if (philo->id % 2 != 0)
		pthread_mutex_unlock(&(philo->l_fork));
	else
		pthread_mutex_unlock((philo->r_fork));
	if (philo->id % 2 != 0)
		pthread_mutex_unlock((philo->r_fork));
	else
		pthread_mutex_unlock(&(philo->l_fork));

	
}

void	wich_eat(t_philo *philo)
{
	//if (philo->data->nb_philo % 2 == 0)
		pair_eating(philo);
	//else
		//eating(philo);

}

void	ft_check_sleep(t_stat *data, t_philo *philo)
{
	long long	normal_duration;
	long long	die_duration;
	long long	sleep_to_die;

	// check data_race
	normal_duration = (philo->last_meal + data->eat + data->sleep);
	die_duration = (philo->last_meal + data->die);
	if (normal_duration > die_duration)
	{
		ft_sleep(data->sleep, data);
	}
	else
	{
		sleep_to_die = die_duration - time_phi();
		ft_sleep(sleep_to_die, data);
		// ###### NEED TO PRINT DEATH
		mutex_dead(data, philo);
		pthread_mutex_lock(&(data->dead));
		data->philo_died = 1;
		pthread_mutex_unlock(&(data->dead));
	}
}

void	*routine(void *philosophers)
{
	int			i;
	t_philo		*philo;
	t_stat		*data;

	i = 0;
	philo = (t_philo *)philosophers;
	data = philo->data;
	if (philo -> id % 2 == 0)
		usleep(100);
	while (check_data_died(data) == 0)
	{
		wich_eat(philo);
		if (check_nb_eat(data) == 1)
		{
			break ;
		}
		print(time_phi(), philo, "is sleeping",data);
		if (check_data_died(data)== 0)
			ft_sleep(data->sleep, data);
		// ft_check_sleep(data, philo);
		// if (check_data_died(data)!= 0)
		// 	return (NULL);
		// else
		// 	return (NULL);
		print(time_phi(), philo, "is thinking",data);
		// usleep((data->die - (philo->last_meal -
		// 			time_phi()) - data ->eat) / 2);
		i++;
	}
	return (NULL);
}