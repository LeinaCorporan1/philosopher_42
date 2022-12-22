/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:06:28 by lcorpora          #+#    #+#             */
/*   Updated: 2022/12/22 04:21:46 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_philo *philosophers, t_stat *data)
{
	long long	i;
	t_philo		*philo;

	i = 0;
	philo = philosophers;
	if (!philo)
		return (0);
	while (i < data->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].is_dead = 0;
		philo[i].last_meal = time_phi();
		philo[i].x_eat = 0;
		philo[i].all_eat = 0;
		philo[i].l_fork = i;
		philo[i].r_fork = (i + 1) % data->nb_philo;
		if (pthread_mutex_init(&philo[i].m_philo, NULL) != 0)
			return (ft_error("Error\n"), 0);
		philo[i].data = data;
		i++;
	}
	philosophers = philo;
	return (1);
}

void	init_must(t_stat *data)
{
	int	i;
	int	init_mutex;
	int	init_fork;

	i = data -> nb_philo;
	init_mutex = 0;
	init_fork = 0;
	while (--i >= 0)
	{
		init_fork = pthread_mutex_init(&(data -> fork[i]), NULL);
		if (init_mutex != 0)
		{
			ft_error("Error d'initialisation mutex");
		}
	}
}

int	init_stat(char **av, t_stat *data)
{
	data->nb_philo = ft_atoi(av[1]);
	if (data->nb_philo > 200)
		return (0);
	data->die = ft_atoi(av[2]);
	data->eat = ft_atoi(av[3]);
	data->sleep = ft_atoi(av[4]);
	data->m_eat = -1;
	if (av[5])
		data->m_eat = ft_atoi(av[5]);
	data->philo_died = 0;
	data->all_ate = 0;
	if (data->nb_philo == 0 || data->m_eat == 0 || data->die == 0)
		return (0);
	init_must(data);
	if (pthread_mutex_init(&data->print, NULL))
		return (0);
	if (pthread_mutex_init(&data->dead, NULL))
		return (0);
	if (init_philo(data->philo, data) == 0)
		return (0);
	return (1);
}
