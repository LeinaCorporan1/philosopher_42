/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:49:56 by lcorpora          #+#    #+#             */
/*   Updated: 2022/12/21 12:49:57 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void	eating(void *philosophers)
{
	t_stat	*data;
	t_philo *philo;

	philo = (t_philo *)philosophers;
	data = philo -> data;
	pthread_mutex_lock((philo->r_fork));
	print(time_phi(),philo, "has taken a fork",data);
	pthread_mutex_lock(&(philo->l_fork));
	print(time_phi(),philo, "has taken a fork",data);
	pthread_mutex_lock(&(data -> eating));
	print(time_phi(),philo, "is eating",data);
	pthread_mutex_lock(&(data->must_eat[philo->id -1]));
	philo -> last_meal = time_phi();
	pthread_mutex_unlock(&(data->must_eat[philo->id -1]));
	pthread_mutex_unlock(&(data -> eating));
	ft_sleep(data->eat,data);
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
	data = philo -> data;
	pthread_mutex_lock(&(philo->l_fork));
	print(time_phi(),philo, "has taken a fork",data);
	pthread_mutex_lock((philo->r_fork));
	print(time_phi(),philo, "has taken a fork",data);
	pthread_mutex_lock(&(data->eating));
	print(time_phi(),philo, "is eating",data);
	pthread_mutex_lock(&(data->must_eat[philo->id - 1]));
	philo -> last_meal = time_phi();
	pthread_mutex_unlock(&(data->must_eat[philo->id - 1]));
	pthread_mutex_unlock(&(data->eating));
	ft_sleep(data->eat,data);
	pthread_mutex_lock(&(data->must_eat[philo->id - 1]));
	philo->x_eat++;
	
	pthread_mutex_unlock((philo->r_fork));
	pthread_mutex_unlock(&(philo->l_fork));
	pthread_mutex_unlock(&(data->must_eat[philo->id - 1]));
}

void	wich_eat(t_philo *philo)
{
	if (philo->data->nb_philo % 2 == 0)
		pair_eating(philo);
	else
		eating(philo);

}

void	*routine(void *philosophers)
{
	int			i;
	t_philo		*philo;
	t_stat	*data;

	i = 0;
	philo = (t_philo *)philosophers;
	data = philo->data;
	if (philo -> id % 2 == 0)
		usleep(100);
	while (check_die_philo2(data) == 0)
	{
		wich_eat(philo);
		if (check_nb_eat(data) == 1)
		{
			break ;
		}
		print(time_phi(), philo, "is sleeping",data);
		ft_sleep(data->sleep, data);
		print(time_phi(), philo, "is thinking",data);
		// usleep((data->die - (philo->last_meal -
		// 			time_phi()) - data ->eat) / 2);
		i++;
	}
	return (NULL);
}