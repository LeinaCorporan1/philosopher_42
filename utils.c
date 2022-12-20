#include "philo.h"

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 97 && c <= 122) || (c >= 65 && c <= 90))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long long i;
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

long long	time_phi(void)
{
	struct timeval time;
	long long i;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	 return((time.tv_sec * 100) + (time.tv_usec / 1000));
}

void	ft_usleep(long long time_info, long long begin)
{
	long long	start;
	long long	i;

	start = time_phi();
	i = 0;
	while (( time_phi() - start) < time_info)
	{
		usleep(time_info / 10);
	}
}

void	print(long long time, t_philo *philo, char *str, t_stat *data)
{
	// if (dead == 1)
		// pthread_mutex_lock(&philo->data->finish);
	pthread_mutex_lock(&philo->data->print);
	if (check_die_philo2(data) == 0)
	{
		// printf("data -> act = % lld my time is %lld\n",philo->data->time_start, time);
		printf("%lld %d %s\n",(time - philo->data->time_start) , philo->id, str);
	}
	pthread_mutex_unlock(&philo->data->print);
	// if (dead == 2)
	// pthread_mutex_unlock(&philo->data->finish);

}
void	ft_sleep(long long time_to, t_stat *data)
{
	long long	begin_sleep;

	begin_sleep = time_phi();
	while ((check_die_philo(data)) == 0)
	{
		if ((time_phi() - begin_sleep) >= time_to)
			break ;
		usleep(50);
	}
}
// void	print(t_stat *data, int numero_philo, char *str)
// {
// 	pthread_mutex_lock(&(data->print));
// 	if (check_die_philo2(data) == 0)
// 	{
// 		printf ("%lli ", (time_phi() - data ->time_start));
// 		printf ("%i ", numero_philo + 1);
// 		printf ("%s\n", str);
// 	}
// 	pthread_mutex_unlock(&(data->print));
// 	return ;
// }
