#include "philo.h"

void	found_dead (t_philo *philosophers)
{
	long long last;
	t_philo *philo;

	philo = (t_philo *)philosophers;
	if ((time_phi() - philo->data->time_start) - philo->last_meal >= philo->data->die)
	{
		// printf("FOUNDEEEDDD inside found dead\n");
		pthread_mutex_lock(&philo->data->dead);
		print(time_phi(), philo, "died");
		philo->is_dead = 1;
		philo->data->philo_died = philo->id;
		pthread_mutex_unlock(&philo->data->dead);
	}
}

// void	*found (void *philosophers)
// {
// 	long long	last;
// 	int			i;
// 	t_philo		*philo;

// 	philo = (t_philo *)philosophers;
// 	printf("id = %d actual time %lld inside found dead %lld - last meal{%lld}\n",philo->id,(time_phi() - philo->data->time_start), (time_phi() - philo->data->time_start) - philo->last_meal, philo->last_meal);
// 		ft_usleep(philo->data->die, philo->data->time_start);

// 	if ((time_phi() - philo->data->time_start) - philo->last_meal > philo->data->die)
// 	{
// 		pthread_mutex_lock(&philo->data->dead);
// 		print(time_phi(), philo, "died");
// 		philo->is_dead = 1;
// 		philo->data->philo_died = philo->id;
// 		// if (pthread_join(philo->phi,NULL) != 0)
// 		// return (0);
// 		pthread_mutex_unlock(&philo->data->dead);
// 	}
// 	return (NULL);
// }


int	as_to_stop(t_philo *philosophers)
{
		int i;
	t_philo *philo;

	i = 0;
	philo = (t_philo *)philosophers;
	// pthread_mutex_lock(&philo->data->eating);
	if (philo->data->philo_died != 0)
	{
		printf("is philo died in as to stop\n");
		i = 1;

	}
	if (philo->data->all_ate == philo->data->m_eat)
	{
		printf("is all_ate in AS TO STOP\n");
		i = 1;
	}
	// pthread_mutex_lock(&philo->data->eating);
	return (i);
}

void	eating(void *philosophers)
{
	t_philo *philo;

	philo = (t_philo *)philosophers;
	if (philo->id % 2 == 0)
		usleep(philo->data->eat/2);
	pthread_mutex_lock(&philo->l_fork);
	print(time_phi(), philo, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	print(time_phi(), philo, "has taken a fork");
	print(time_phi(), philo, "is eating");
	ft_usleep(philo->data->eat, philo->data->time_start);
	pthread_mutex_lock(&philo->data->eating);
	philo->last_meal = time_phi() - philo->data->time_start;
	philo->as_eaten++;
	// printf("as eatin %d = %d\n", philo->id, philo->as_eaten);
	if (philo->as_eaten == philo->data->m_eat)
		philo->data->all_ate++;
	printf("aall eating %d = %lld as_eaten = %d meat= %lld\n", philo->id, philo->data->all_ate,philo->as_eaten, philo->data->m_eat);
	pthread_mutex_unlock(&philo->data->eating);
	// printf("aall eating %d = %lld\n", philo->id, philo->data->all_ate);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);

}

void	*routine(void *philosophers)
{
	long long i;
	t_philo *philo;

	i = 0;
	philo = (t_philo *)philosophers;
	printf("inside of routine dead %lld\n", philo->data->philo_died);
	while (!as_to_stop(philo))
	{
		if (philo->data->philo_died != 0)
			return (NULL);
		eating(philo);
	// printf("aall eating %d = %lld meat= %lld\n", philo->id, philo->data->all_ate, philo->data->m_eat);
		if (as_to_stop(philo))
		{
			// printf ()
			return (NULL);
		}
	// printf("aall eating %d = %lld meat= %lld\n", philo->id, philo->data->all_ate, philo->data->m_eat);
		print(time_phi(), philo, "is sleeping");
		ft_usleep(philo->data->sleep, philo->data->time_start);
		print(time_phi(), philo, "is thinking");
	}
		if (pthread_join(philo->died,NULL) != 0)
			return (0);

	return (NULL);
}

int	tr(t_philo *philo, t_stat data)
{
	long long	i;
	i = 0;
	// 	printf("thed id 0f philo before %lld\n", data.nb_philo);
	// while (i < data.nb_philo)
	// {
	// 	printf("thed id 0f philo[%lld] = [%d]\n", i, philo[i].id);
	// 	i++;
	// }
	//  i  = 0;
	 philo->data->time_start = time_phi();
	 printf("data time = %lld\n", data.time_start);
	while(i < data.nb_philo)
	{
		printf("is inside\n");
		if (pthread_create(&philo[i].phi,NULL, &routine, &philo[i]) != 0)
			return (0);
		i ++;
	}
	// while(!data.philo_died)
	// {
	// 	found_dead(philo);
	// }
	i = 0;
	while(i < data.nb_philo)
	{
		if (pthread_join(philo[i].phi,NULL) != 0)
			return (0);
		i ++;
	}

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
	if (init_philo(&philo ,&data))
	printf("done data nb_philo %lld\n", data.nb_philo);
	tr(philo, data);
		return (1);
}
// je dois mettre la partie qui travail dans une autre fonction pour renvoyer l'addresse de philo
