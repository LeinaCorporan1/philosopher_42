#include "philo.h"

// int	init_fork(t_stat *data)
// {
// 	long long i;

// 	i = 0;
// 	while (i < data->nb_philo)
// 	{
// 		if (pthread_mutex_init(&data->fork[i], NULL))
// 			return (0);
// 		// pthread_mutex_init(&data.fork[i], NULL);
// 		i++;
// 	}
// 	if (pthread_mutex_init(&data->print, NULL))
// 		return (0);
// 	return (1);
// }

int	init_philo(t_philo *philo, t_stat *data)
{
	int i;

	i = 0;
	philo = malloc(sizeof(t_philo) * data->nb_philo + 1);
	if(!philo)
		return (0);
	while(i < data->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].is_dead = 0;
		// philo[i].is_dead = 0;
		// philo[i].l_fork = pthread_mutex_init(&philo[i].l_fork ,NULL);
		pthread_mutex_init(&philo[i].l_fork ,NULL);
		if(i != data->nb_philo - 1)
		philo[i].r_fork = &philo[i + 1].l_fork;
		else
		philo[i].r_fork = &philo[0].l_fork;
		// if (i != 0)
		// 	philo[i].r_fork = (i + 1) % nb_philo;
		// else
		// 	philo[i].r_fork = nb_philo;
		printf("i = %d id %d \n",i , philo[i].id);
		philo[i].data = data;
		i++;
	}
	return (1);
}

int	init_stat(char **av, t_stat *data)
{
	data->nb_philo = ft_atoi(av[1]);
	data->die = ft_atoi(av[2]);
	data->eat = ft_atoi(av[3]);
	data->sleep = ft_atoi(av[4]);
	if (av[5])
		data->m_eat = ft_atoi(av[5]);
	else
		data->m_eat = 0;
	data->philo_died = 0;
	return (1);
// 	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
// 	if (!data->philo)
// 		return (0);
// 	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
// 	if (!data->fork)
// 		return (0);
// 	if (!init_philo(data))
// 		return (0);
// 	if (!init_fork(data))
// 		return (0);
}
