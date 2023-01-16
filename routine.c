/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:49:56 by lcorpora          #+#    #+#             */
/*   Updated: 2023/01/16 18:10:00 by lcorpora         ###   ########.fr       */
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
	pthread_mutex_lock((&philo->m_philo));
	philo -> last_meal = time_phi();
	philo->x_eat++;
	pthread_mutex_unlock((&philo->m_philo));
	ft_sleep(philo->data->eat);
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
	// time to death Death time = 350
	// eat time = 200
	// sleep time = 100

	// think time = ???

	// Eat time = Sleep + (think time)

	// unit time = 50

	//				
	// Philo 1 : |EEEE|SST*T|EEEE|...
	// Philo 2 : |TTTT|EEE*E|SSTT|...


// ############ NORMAL NO DEATH
	// time to death Death time = 380
	// eat time = 200
	// sleep time = 100

	// think time = 100 (eat time - think time)

	// (Eat time == Sleep + (think time)

	// die_duration T : 380 ms

	long long	think_time;
	long long	normal_duration;
	long long	die_duration;
	long long	sleep_to_die;
	// printf("\nThinking ");
	print(time_phi(), philo, "is thinking",data);
	if (data->eat > data->sleep)
	{
		think_time = data->eat - data->sleep; // 100 
		// printf("my think time is %lld for philo {%d}\n", think_time, philo->id);
		normal_duration = philo->last_meal + data->eat + data->sleep + think_time;
		die_duration = (philo->last_meal + data->die);
		sleep_to_die = die_duration - time_phi();

		if (normal_duration > die_duration)
		{
			usleep(sleep_to_die);

			// ###### NEED TO PRINT DEATH remplace with mutex dead
			printf("il est mort rooooooo\n");
			mutex_dead(data, philo);
			pthread_mutex_lock(&(data->dead));
			data->philo_died = 1;
			pthread_mutex_unlock(&(data->dead));
		}
		else
			ft_sleep(think_time);
	}
}

void	*routine(void *philosophers)
{
	t_philo		*philo;
	t_stat		*data;

	philo = (t_philo *)philosophers;
	data = philo->data;
	// printf("last meal = %lld de philo = %d\n", philo->last_meal, philo->id);
	// if (philo->id % 2 == 0)
	// 	ft_sleep (100);
	// print(time_phi(), philo, "IS INSIDE OF IITTTT", philo->data);
	while (check_data_died(data) == 0)
	{
		pair_eating(philo);
		print(time_phi(), philo, "is sleeping", data);
		ft_sleep(data->sleep);
		// print(time_phi(), philo, "is thinking", data);
		ft_check_death_inside_think(data, philo);
	// // 	if (data->sleep < data->eat)
			// ft_sleep(100, data);
	}
	return (NULL);
}
