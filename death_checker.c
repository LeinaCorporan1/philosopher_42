/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:06:10 by lcorpora          #+#    #+#             */
/*   Updated: 2022/12/21 16:46:37 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	check_in_data_death(t_stat *data) before changed
// {
// 	int	dead;

// 	dead = -1;
// 	pthread_mutex_lock(&(data->dead));
// 	dead = data->philo_died;
// 	pthread_mutex_unlock(&(data->dead));
// 	if (dead == 1)//voir si je met superieur a 1 ou egal
// 		return (1);
// 	return (0);
// }

int	mutex_dead(t_stat *data, t_philo *philo)
{
	print (time_phi(), data->philo, "died",data);
	pthread_mutex_lock(&(data->dead));
	data -> philo_died = 1;
	pthread_mutex_unlock(&(data->dead));
	return (1);
}

int	check_data_died(t_stat *data)
{
	int	retour;

	retour = -1;
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
			// finish_all_mutex(data, philo);
			// exit_mutex(data);
			break ;
		}
		i = data_all_eat1(data);
	}
}