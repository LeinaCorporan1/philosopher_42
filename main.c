#include "philo.h"

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 97 && c <= 122) || (c >= 65 && c <= 90))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == '\v' || str[i]
		== '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	while (((str[i] == '-') || (str[i] == '+')) && ft_isalnum(str[i + 1]))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}



int	init_fork(t_stat *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL))
			return (0);
		i++;
	}
	if (pthread_mutex_init(&data->print, NULL))
		return (0);
	return (1);
}

int	init_philo(t_stat *data)
{
	int i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) *data->nb_philo + 1);
	if(!data->philo)
		return (0);
	while(i < data->nb_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].is_dead = 0;
		// data->philo[i].is_dead = 0;
		data->philo[i].l_fork = i;
		if (i != 0)
			data->philo[i].r_fork = (i + 1) % data->nb_philo;
		else
			data->philo[i].r_fork = data->nb_philo;
		printf("i = %d id %d left = %d right = %d\n",i , data->philo[i].id, data->philo[i].l_fork, data->philo[i].r_fork);
		data->philo[i].data = data;
		i++;
	}
	return (1);
}

long long	time_phi(void)
{
	struct timeval time;
	long long i;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	 return((time.tv_sec * 100) + (time.tv_usec / 1000));
	 printf ("i  = %lli tv_sec = %li tv_unsec = %li \n", i , (time.tv_sec * 100), (time.tv_usec / 1000));
}

void	ft_usleep(long long time_info)
{
	long long	start;

	start = time_phi();
	while (time_phi() - start <= time_info)
		usleep(time_info / 10);
}



void	print(long long time, t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%lli %d %s\n", time - philo->data->act_time, philo->id, str);
	pthread_mutex_unlock(&philo->data->print);
}

int	init_stat(char **av, t_stat *data)
{
	data->nb_philo = ft_atoi(av[1]);
	data->die = ft_atoi(av[2]);
	data->eat = ft_atoi(av[3]);
	data->sleep = ft_atoi(av[4]);
	if (av[5])
		data->m_eat = ft_atoi(av[5]);
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		return (0);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->fork)
		return (0);
	if (!init_philo(data))
		return (0);
	if (!init_fork(data))
		return (0);
}

int	as_to_stop(t_philo *philosophers)
{
		int	i;
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
		usleep(15000);
	pthread_mutex_lock(&philo->data->fork[philo->l_fork]);
	// printf("philo {%d} is taken left fork [%d]\n",philo-> id, philo->l_fork);
	print(time_phi(), philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->fork[philo->r_fork]);
	print(time_phi(), philo, "has taken a fork");

	// printf("philo {%d} is taken right fork [%d]\n",philo-> id, philo->r_fork);
	print(time_phi(), philo, "is eating");
	ft_usleep(philo->data->eat);
	philo->as_eaten++;
	pthread_mutex_unlock(&philo->data->fork[philo->l_fork]);
	pthread_mutex_unlock(&philo->data->fork[philo->r_fork]);

}

int	found_dead (t_philo *philosopher)
{
	if ()
}

void	*journey(void *philosophers)
{
	int	i;
	t_philo *philo;

	i = 0;
	philo = (t_philo *)philosophers;
	while (philo->as_eaten != philo->data->m_eat)
	{
		test(philo);
		//printf("philo[%i] as eaten %d\n",philo->id, philo->as_eaten);

	}
}

int main(int ac, char **av)
{
	t_stat data;

	// data = NULL;
	if (ac != 5 && ac != 6)
		return (0);
	if (init_stat(av, &data) == 0)
		return (0);
	printf("done\n");
	int i;
	i = 0;

	while (i < data.nb_philo)
	{
		printf("thed id 0f philo[%d] = [%d]\n", i, data.philo[i].id);
		i++;
	}
	 i  = 0;
	 data.act_time = time_phi();
	while(i < data.nb_philo)
	{
		pthread_mutex_init(&data.fork[i], NULL);
		if (pthread_create(&data.philo[i].phi,NULL, &journey, &data.philo[i]) != 0)
			return (0);
		printf ("created at %d\n",i);
		i ++;
	}
	// printf("OUTSIIIDEE\n");
	i = 0;

	while(i < data.nb_philo)
	{
		if (pthread_join(data.philo[i].phi,NULL) != 0)
			return (0);
		i ++;
	}
		return (1);
}
