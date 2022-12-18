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

	// printf("inside of time\n");
	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	// i = (time.tv_sec * 100) + (time.tv_usec / 1000);
	//  printf ("i  = %lli tv_sec = %li tv_unsec = %li \n", i , (time.tv_sec * 100), (time.tv_usec / 1000));
	 return((time.tv_sec * 100) + (time.tv_usec / 1000));
}

void	ft_usleep(long long time_info)
{
	long long	start;
	long long	i;

	start = time_phi();
	i = 0;
	// printf("is usleep\n");
	while ((i = time_phi())- start <= time_info)
	{
		printf("timmee %lld start %lld\n",i,start);
		usleep(time_info / 10);
	}

}

void	print(long long time, t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%lli %d %s\n", time - philo->data->act_time, philo->id, str);
	pthread_mutex_unlock(&philo->data->print);
}
