/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:49:56 by lcorpora          #+#    #+#             */
/*   Updated: 2022/12/22 04:19:56 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pair_eating(void *philosophers)
{
	t_philo	*philo;

	philo = (t_philo *)philosophers;
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock((&philo->data->fork[philo->r_fork]));
		pthread_mutex_lock(&philo->data->fork[philo->l_fork]);
	}
	else
	{
		usleep(5000);
		pthread_mutex_lock(&philo->data->fork[philo->l_fork]);
		pthread_mutex_lock((&philo->data->fork[philo->r_fork]));
	}
	print(time_phi(), philo, "has taken a fork", philo->data);
	print(time_phi(), philo, "has taken a fork", philo->data);
	print(time_phi(), philo, "is eating", philo->data);
	pthread_mutex_lock((&philo->m_philo));
	philo -> last_meal = time_phi();
	philo->x_eat++;
	pthread_mutex_unlock((&philo->m_philo));
	ft_sleep(philo->data->eat, philo->data);
	pthread_mutex_unlock(&philo->data->fork[philo->l_fork]);
	pthread_mutex_unlock((&philo->data->fork[philo->r_fork]));
}

void	*routine(void *philosophers)
{
	t_philo		*philo;
	t_stat		*data;

	philo = (t_philo *)philosophers;
	data = philo->data;
	while (check_data_died(data) == 0)
	{
		pair_eating(philo);
		print(time_phi(), philo, "is sleeping", data);
		ft_sleep(data->sleep, data);
		print(time_phi(), philo, "is thinking", data);
	// 	if (data->sleep < data->eat)
			usleep(100);
	}
	return (NULL);
}
