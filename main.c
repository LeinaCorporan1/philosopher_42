#include "philo.h"

void	found_dead (t_philo *philosophers)
{
	long long last;
	t_philo *philo;

	philo = (t_philo *)philosophers;
	printf("inside found dead\n");
	if ((time_phi() - philo->data->act_time) - philo->last_meal >= philo->data->die)
	{
		printf("FOUNDEEEDDD inside found dead\n");
		pthread_mutex_lock(&philo->data->dead);
		print(time_phi(), philo, "is dead");
		philo->is_dead = 1;
		philo->data->philo_died = philo->id;
		pthread_mutex_unlock(&philo->data->dead);
	}
}


int	as_to_stop(t_philo *philosophers)
{
		long long i;
	t_philo *philo;

	i = 0;
	philo = (t_philo *)philosophers;
	if (philo->is_dead)
		return (0);
}

void	test(void *philosophers)
{
	t_philo *philo;

	philo = (t_philo *)philosophers;
	if (philo->id % 2 == 0)
		usleep(150);
	pthread_mutex_lock(&philo->l_fork);
	// printf("philo {%d} is taken left fork [%d]\n",philo-> id, philo->l_fork);
	print(time_phi(), philo, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	print(time_phi(), philo, "has taken a fork");

	// printf("philo {%d} is taken right fork [%d]\n",philo-> id, philo->r_fork);
	print(time_phi(), philo, "is eating");
	ft_usleep(philo->data->eat);
	philo->last_meal = time_phi() - philo->data->act_time;
	philo->as_eaten++;
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);

}

void	*journey(void *philosophers)
{
	long long i;
	t_philo *philo;

	i = 0;
	philo = (t_philo *)philosophers;
	printf("inside of journey dead %lld\n", philo->data->philo_died);
	while (!philo->data->philo_died)
	{
		test(philo);
		// found_dead(philo);
		if (philo->as_eaten == philo->data->m_eat)
			return (NULL);
		print(time_phi(), philo, "is sleeping");
		ft_usleep(philo->data->sleep);
		print(time_phi(), philo, "is thinking");
		// printf("phlo[%i] as eaten %d\n",philo->id, philo->as_eaten);
	}
	return (NULL);
}

int main(int ac, char **av)
{
	t_stat data;
	t_philo	*philo;

	// data = NULL;
	if (ac != 5 && ac != 6)
		return (0);
	if (init_stat(av, &data) == 0)
		return (0);
	if (init_philo(philo ,&data))
	printf("done\n");
	long long	i;
	i = 0;

	while (i < data.nb_philo)
	{
		printf("thed id 0f philo[%lld] = [%d]\n", i, philo[i].id);
		i++;
	}
	 i  = 0;
	 data.act_time = time_phi();
	while(i < data.nb_philo)
	{
		// pthread_mutex_init(&data.fork[i], NULL);
		if (pthread_create(&philo[i].phi,NULL, &journey, &philo[i]) != 0)
			return (0);
		printf ("created at %lld\n",i);
		i ++;
	}
	printf("OUTSIIIDEE\n");
	if (data.philo_died != 0)
		return (0);
	i = 0;

	while(i < data.nb_philo)
	{
		if (pthread_join(philo[i].phi,NULL) != 0)
			return (0);
		i ++;
	}
		return (1);
}
