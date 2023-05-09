/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 03:08:53 by lcorpora          #+#    #+#             */
/*   Updated: 2023/01/27 11:40:25 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	finish_all_mutex(t_stat *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(philo[i].phi, NULL);
		i++;
	}
}

int	thread_philo(t_philo *philo, t_stat data)
{
	long long	i;

	i = 0;
	philo->data->time_start = time_phi();
	while (i < data.nb_philo)
	{
		if (pthread_create(&philo[i].phi, NULL, &routine, &philo[i]) != 0)
			return (0);
		i ++;
	}
	return (1);
}

void	one_eating(void *philosophers)
{
	t_philo	*philo;

	philo = (t_philo *)philosophers;
	philo->data->time_start = time_phi();
	print(time_phi(), philo, "has taken a fork");
	ft_usleep(philo->data->die, philo->data);
	print (time_phi(), philo, "died");
}

int	main(int ac, char **av)
{
	t_stat	data;
	t_philo	*philo;

	if (ac != 5 && ac != 6)
		return (ft_error("Invalid number of arguments\n"), 0);
	if (check_args(av))
		return (0);
	if (init_stat(av, &data) == 0)
		return (ft_error("imposible to initialize data\n"), 0);
	if (init_philo(&philo, &data) == 0)
		return (ft_error("Impossible to initialize philo\n"), 0);
	if (data.nb_philo != 1 && thread_philo(philo, data))
	{
		ft_monitoring(&data, philo);
		finish_all_mutex(&data, philo);
	}
	else
		one_eating(philo);
	free(philo);
	return (1);
}
