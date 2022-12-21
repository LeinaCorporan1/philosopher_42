/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:50:22 by lcorpora          #+#    #+#             */
/*   Updated: 2022/12/21 17:06:04 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	 return((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print(long long time, t_philo *philo, char *str, t_stat *data)
{

	pthread_mutex_lock(&philo->data->print);
	if (check_data_died(data) == 0)
	{
		printf("%lld %d %s\n",(time - philo->data->time_start) , philo->id, str);
	}
	pthread_mutex_unlock(&philo->data->print);

}
void	ft_sleep(long long time_to, t_stat *data)
{
	long long	begin_sleep;

	begin_sleep = time_phi();
	while (((check_die_philo(data)) == 0))
	{
		if ((time_phi() - begin_sleep) >= time_to)
			break ;
		usleep(50);
	}
}
