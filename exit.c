/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corporan <corporan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:05:26 by lcorpora          #+#    #+#             */
/*   Updated: 2023/01/18 02:34:42 by corporan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	finish_all_mutex(t_stat *data, pthread_t *phi)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
		pthread_join(phi[i], NULL);
}

void	exit_mutex(t_stat *data)
{
	int	i;

	i = -1;
	while (i++ < data->nb_philo)
	{
		// pthread_mutex_destroy(&(data->philo[i].m_philo));
		pthread_mutex_destroy(&(data->fork[i]));
	}
	pthread_mutex_destroy(&(data->dead));
	pthread_mutex_destroy(&(data->print));
}
