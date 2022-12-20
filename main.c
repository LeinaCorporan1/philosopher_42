#include "philo.h"

void	found_dead (t_philo *philosophers, t_stat *data)
{
	long long last;
	int i;
	t_philo *philo;

	philo = (t_philo *)philosophers;
	i = -1;
	printf("inside found dead begin\n");
	// if (philo->data->all_ate != philo->data->nb_philo || philo->data->philo_died)
	// 	return ;
	printf("inside after found dead begin\n");

	// while(!philo->data->philo_died)
	// {
	// 	ft_usleep(philo->data->die, 0);
	// 	printf("die at = %lld and start %lld\n",philo->data->die, time_phi() - philo->data->time_start);

	// 	if (philo->last_meal != -1 && (time_phi() - philo->data->time_start) - philo->last_meal >= philo->data->die)
	// {

	// 	pthread_mutex_lock(&philo->data->dead);
	// 	print(time_phi(), philo, "died", 1);
	// 	philo->is_dead = 1;
	// 	philo->data->philo_died = philo->id;
	// 	printf("FOUNDEEEDDD inside found dead  data-> died %lld id = %d\n", philo->data->philo_died, philo->id);
	// 	pthread_mutex_unlock(&philo->data->dead);
	// }
		while(data->all_ate != data->nb_philo)
		{
			i = -1;
			while (++i < data->nb_philo && !(data->philo_died))
		{
			// usleep(philo[i]->data)
			printf("\033[0;32minside zhile for found dead\033[0m\n");
			pthread_mutex_lock(&(philo[i].data->dead));
			if ((philo[i].last_meal - time_phi()) > philo[i].data->die)
			{
				philo[i].is_dead = 1;

				print( time_phi(),&philo[i], "died",philo[i].data);
				philo[i].data->philo_died = 1;
			}
			pthread_mutex_unlock(&(philo[i].data->dead));
			usleep(100);
		}
				if (data->philo_died)
			break ;
		i = 0;
		while (data->m_eat != -1 && i < data->nb_philo && philo[i].as_eaten >= data->m_eat)
			i++;
		if (i == data->nb_philo)
			data->all_ate = i;
		}

	// i++;
	// }
	// *philosophers = philo;
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
int	check_die_philo2(t_stat *data)
{
	int	dead;

	dead = -1;
	pthread_mutex_lock(&(data->dead));
	dead = data->philo_died;
	pthread_mutex_unlock(&(data->dead));
	if (dead == 1)//voir si je met superieur a 1 ou egal
		return (1);
	return (0);
}

int	mutex_dead(t_stat *data, t_philo *philo)
{
	print (time_phi(), data->philo, "died",data);
	pthread_mutex_lock(&(data -> dead));
	data -> philo_died = 1;
	pthread_mutex_unlock(&(data -> dead));
	return (1);
}

int	check_nb_eat(t_stat *data)
{
	int	i;

	i = data -> nb_philo - 1;
	if (data -> m_eat == -1)
		return (0);
	i = data -> nb_philo;
	while (--i >= 0)
	{
		pthread_mutex_lock(&(data -> must_eat[i]));
		if (data -> philo[i].x_eat < data->m_eat)
		{
			pthread_mutex_unlock(&(data->must_eat[i]));
			return (0);
		}
		pthread_mutex_unlock(&(data->must_eat[i]));
	}
	return (1);
}

int	mutex_all_eat(t_stat *data)
{
	pthread_mutex_lock(&(data->dead));
	data->all_ate = 1;
	pthread_mutex_unlock(&(data->dead));
	return (1);
}

int	data_all_eat1(t_stat *data)
{
	if (check_nb_eat(data) == 1)
		mutex_all_eat(data);
	return (check_nb_eat(data));
}

int	check_data_died(t_stat *data)
{
	int	retour;

	retour = 0;
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
			break ;
		i = data_all_eat1(data);
	}
}

void	eating(void *philosophers)
{
	t_stat	*data;
	t_philo *philo;

	philo = (t_philo *)philosophers;
	// if (philo->id % 2 == 0)
	// 	usleep (1);
	data = philo -> data;
	pthread_mutex_lock((philo->r_fork));
	print(time_phi(),philo, "has taken a fork",data);
	pthread_mutex_lock(&(philo->l_fork));
	print(time_phi(),philo, "has taken a fork",data);
	pthread_mutex_lock(&(data -> eating));
	print(time_phi(),philo, "is eating",data);
	pthread_mutex_lock(&(data->must_eat[philo->id]));
	philo -> last_meal = time_phi();
	pthread_mutex_unlock(&(data->must_eat[philo->id]));
	pthread_mutex_unlock(&(data -> eating));
	ft_sleep(data->eat,data);
	pthread_mutex_lock(&(data->must_eat[philo->id]));
	philo->x_eat++;
	pthread_mutex_unlock((philo->r_fork));
	pthread_mutex_unlock(&(philo->l_fork));
	pthread_mutex_unlock(&(data->must_eat[philo->id]));

}

void	pair_eating(void *philosophers)
{
	t_stat	*data;
	t_philo *philo;

	philo = (t_philo *)philosophers;
	// if (philo->id % 2 == 0)
	// 	usleep (1);
	data = philo -> data;
	pthread_mutex_lock(&(philo->l_fork));
	print(time_phi(),philo, "has taken a fork",data);
	pthread_mutex_lock((philo->r_fork));
	print(time_phi(),philo, "has taken a fork",data);
	pthread_mutex_lock(&(data -> eating));
	print(time_phi(),philo, "is eating",data);
	pthread_mutex_lock(&(data->must_eat[philo->id]));
	philo -> last_meal = time_phi();
	pthread_mutex_unlock(&(data->must_eat[philo->id]));
	pthread_mutex_unlock(&(data->eating));
	ft_sleep(data->eat,data);
	pthread_mutex_lock(&(data->must_eat[philo->id]));
	philo->x_eat++;
	pthread_mutex_unlock(&(philo->l_fork));
	pthread_mutex_unlock((philo->r_fork));
	pthread_mutex_unlock(&(data->must_eat[philo->id]));

}

void	wich_eat(t_philo *philo)
{
	if (philo->data->nb_philo % 2 == 0)
		pair_eating(philo);
	else
		eating(philo);

}

void	*routine(void *philosophers)
{
	int			i;
	t_philo		*philo;
	t_stat	*data;

	i = 0;
	philo = (t_philo *)philosophers;
	data = philo->data;
	if (philo -> id % 2 == 0)
		usleep(100);
	while (check_die_philo2(data) == 0)
	{
		wich_eat(philo);
		if (check_nb_eat(data) == 1)
		{
			break ;
		}
		print(time_phi(), philo, "is sleeping",data);
		ft_sleep(data->sleep, data);
		print(time_phi(), philo, "is thinking",data);
		usleep((data->die - (philo->last_meal -
					time_phi()) - data ->eat) / 2);
		i++;
	}
	return (NULL);
}

void	finish_all_mutex(t_stat *data, t_philo *philo)
{
	int	i;

	i = data -> nb_philo;
	while (--i >= 0)
	{
		pthread_join(philo[i].phi, NULL);
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
	i =data -> nb_philo;
	free (data ->must_eat);
}

int	do_pthread(t_stat *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = data -> philo;
	data -> time_start = time_phi();
	while (i < data -> nb_philo)
	{
		if (pthread_create(&(philo[i].phi), NULL,routine, &(philo[i])))
		{
			// ft_error("Error");
			exit (1);
		}
		pthread_mutex_lock(&(data->must_eat[i]));
		philo[i].last_meal = time_phi();
		pthread_mutex_unlock(&(data->must_eat[i]));
		i++;
	}
	death_checker( data, data->philo);
	finish_all_mutex(data, philo);
	exit_mutex(data);
	return (0);
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
	do_pthread(&data);
		return (1);
}
//je dois checker pk ca marche pas avec ./philo 4 2147483647 200 200 et aussi si il y a que 1
