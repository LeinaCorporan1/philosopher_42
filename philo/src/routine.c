/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 04:44:22 by lcorpora          #+#    #+#             */
/*   Updated: 2023/01/27 11:41:32 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	locking_fork(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock((&philo->l_fork));
		print(time_phi(), philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print(time_phi(), philo, "has taken a fork");
		pthread_mutex_lock((&philo->l_fork));
	}
	print(time_phi(), philo, "has taken a fork");
}

void	eating(void *philosophers)
{
	t_philo	*philo;

	philo = (t_philo *)philosophers;
	locking_fork(philo);
	print(time_phi(), philo, "is eating");
	pthread_mutex_lock(&(philo->m_philo));
	philo -> last_meal = time_phi();
	philo->as_eaten++;
	pthread_mutex_unlock(&(philo->m_philo));
	ft_usleep(philo->data->eat, philo->data);
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock((philo->r_fork));
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock((&philo->l_fork));
	}
}

void	*routine(void *philosophers)
{
	t_philo		*philo;

	philo = (t_philo *)philosophers;
	if (philo->id % 2 == 0)
		usleep(200);
	while (!check_data_died(philo->data))
	{
		eating(philo);
		print(time_phi(), philo, "is sleeping");
		ft_usleep(philo->data->sleep, philo->data);
		print(time_phi(), philo, "is thinking");
		ft_usleep(philo->data->think, philo->data);
	}
	return (NULL);
}
