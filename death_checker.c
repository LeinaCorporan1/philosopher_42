/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:06:10 by lcorpora          #+#    #+#             */
/*   Updated: 2023/01/16 17:38:07 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_dead(t_stat *data, t_philo *philo)
{
	print (time_phi(), data->philo, "died", data);
	pthread_mutex_lock(&(data->dead));
	data -> philo_died = 1;
	pthread_mutex_unlock(&(data->dead));
	return (1);
}

int	check_data_died(t_stat *data)
{
	pthread_mutex_lock(&(data->dead));
	if (data->philo_died == 1 || data->all_ate == 1)
	{	
		pthread_mutex_unlock(&(data->dead));
		return (1);
	}
	pthread_mutex_unlock(&(data->dead));
	return (0);
}

void	death_checker(t_stat *data, t_philo *philo)
{
	int	i;

	// usleep(5000);
	while (check_nb_eat(data) == 0)
	{
		i = -1;
		while (++i < data -> nb_philo)
		{
			if ((time_phi() - philo[i].last_meal) > data->die)
			{
				// printf("time = %lld  last meal == %lld \n", time_phi() - philo[i].last_meal, philo[i].last_meal);
				mutex_dead(data, &philo[i]);
				break ;
			}
		}
		// usleep(100);
	}
}
