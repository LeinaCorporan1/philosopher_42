/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:05:26 by lcorpora          #+#    #+#             */
/*   Updated: 2022/12/21 17:14:07 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	finish_all_mutex(t_stat *data, t_philo *philo)
{
	int	i;

	i = data->nb_philo;
	while (--i >= 0)
	{
		pthread_join(philo[i].phi, NULL);
		//pthread_mutex_destroy(&(philo[i].l_fork));
	}
}

void	exit_mutex(t_stat *data)
{
	int	i;

	i =data -> nb_philo;
	while (--i >= 0)
	{
		pthread_mutex_destroy(&(data->must_eat[i]));
	}
	i = data->nb_philo;
	free(data->must_eat);
}