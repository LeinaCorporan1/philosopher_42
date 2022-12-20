#include "philo.h"

int	init_philo(t_philo **philosophers, t_stat *data)
{
	long long i;
	t_philo	*philo;

	i = 0;
	philo = *philosophers;
	philo = malloc(sizeof(t_philo) * data->nb_philo + 1);
	if(!philo)
		return (0);
	// printf("hellooooo\n");
	while(i < data->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].is_dead = 0;
		philo[i].last_meal = 0;
		philo[i].as_eaten = 0;
		philo[i].x_eat = 0;
		philo[i].all_eat = 0;
		pthread_mutex_init(&philo[i].l_fork ,NULL);
		if(i != data->nb_philo - 1)
		philo[i].r_fork = &philo[i + 1].l_fork;
		else
		philo[i].r_fork = &philo[0].l_fork;
		philo[i].data = data;
		i++;
	}
	*philosophers = philo;
	return (1);
}

int	init_must(t_stat *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->must_eat[i], NULL))
			return (0);
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
	printf ("time to die %lld\n", data->die);
	if (av[5])
		data->m_eat = ft_atoi(av[5]);
	else
		data->m_eat = -1;
	data->philo_died = 0;
	data->all_ate = 0;

	data->must_eat = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!init_must(data))
		return(0);
	if (pthread_mutex_init(&data->print, NULL))
		return (0);
	if (pthread_mutex_init(&data->eating, NULL))
		return (0);
	if (pthread_mutex_init(&data->dead, NULL))
		return (0);
	if (pthread_mutex_init(&data->finish, NULL))
		return (0);
	init_philo(&data->philo, data);
	return (1);
}
