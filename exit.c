/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:05:26 by lcorpora          #+#    #+#             */
/*   Updated: 2022/12/22 03:48:31 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	finish_all_mutex(t_stat *data, t_philo *philo)
{
	int	i;

	i = data->nb_philo;
	while (--i >= 0)
		pthread_join(philo[i].phi, NULL);
}

void	exit_mutex(t_stat *data)
{
	int	i;

	i = data -> nb_philo;
	while (--i >= 0)
	{
		pthread_mutex_destroy(&(data->philo[i].m_philo));
		pthread_mutex_destroy(&(data->fork[i]));
	}
	pthread_mutex_destroy(&(data->dead));
	pthread_mutex_destroy(&(data->print));
	i = data->nb_philo;
}
