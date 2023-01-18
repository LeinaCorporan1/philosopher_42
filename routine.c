/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corporan <corporan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:49:56 by lcorpora          #+#    #+#             */
/*   Updated: 2023/01/18 02:40:15 by corporan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pair_eating(void *philosophers)
{
	t_philo	*philo;

	philo = (t_philo *)philosophers;
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock((&philo->data->fork[philo->l_fork]));
		pthread_mutex_lock(&philo->data->fork[philo->r_fork]);
	}
	else
	{
		// usleep(500);
		pthread_mutex_lock(&philo->data->fork[philo->r_fork]);
		pthread_mutex_lock((&philo->data->fork[philo->l_fork]));
	}
	print(time_phi(), philo, "has taken a fork", philo->data);
	print(time_phi(), philo, "has taken a fork", philo->data);
	print(time_phi(), philo, "is eating", philo->data);
	// pthread_mutex_lock((&philo->m_philo));
	philo -> last_meal = time_phi();
	philo->x_eat++;
	// pthread_mutex_unlock((&philo->m_philo));
	ft_usleep(philo->data->eat);
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(&philo->data->fork[philo->l_fork]);
		pthread_mutex_unlock((&philo->data->fork[philo->r_fork]));
	}
	else
	{
		pthread_mutex_unlock(&philo->data->fork[philo->r_fork]);
		pthread_mutex_unlock((&philo->data->fork[philo->l_fork]));
	}
}

void	ft_check_death_inside_think(t_stat *data, t_philo *philo)
{
	long long	think_time;
	long long	normal_duration;
	long long	die_duration;
	long long	sleep_to_die;
	print(time_phi(), philo, "is thinking",data);
	if (data->eat > data->sleep)
	{
		think_time = data->eat - data->sleep;
		normal_duration = philo->last_meal + data->eat + data->sleep + think_time;
		die_duration = (philo->last_meal + data->die);
		sleep_to_die = die_duration - time_phi();

		if (normal_duration > die_duration)
		{
			usleep(sleep_to_die);
			mutex_dead(data, philo);
			// pthread_mutex_lock(&(data->dead));
			data->philo_died = 1;
			// pthread_mutex_unlock(&(data->dead));
		}
		else
			ft_usleep(think_time);
	}
}

void	*routine(void *philosophers)
{
	t_philo		*philo;
	t_stat		*data;

	philo = (t_philo *)philosophers;
	data = philo->data;
	while (1)
	{
		pair_eating(philo);
		print(time_phi(), philo, "is sleeping", data);
		ft_usleep(data->sleep);
		ft_check_death_inside_think(data, philo);
	}
	return (NULL);
}
