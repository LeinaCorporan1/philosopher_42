#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

typedef	struct s_philo
{
	// int	r_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	l_fork;
	int	id;
	int	is_dead;
	int	as_eaten;
	long long	last_meal;
	struct s_stat	*data;
	pthread_t phi;
} t_philo;

typedef struct s_stat
{
	long long	eat;
	long long	sleep;
	long long	nb_philo;
	long long	m_eat;
	long long	die;
	long long	philo_died;
	long long	act_time;
	// t_philo	*philo;
	// pthread_mutex_t	*fork;
	pthread_mutex_t	dead;
	pthread_mutex_t	print;
}	t_stat;


int	init_stat(char **av, t_stat *data);
int	init_philo(t_philo **philo, t_stat *data);

void	ft_usleep(long long time_info, long long begin);
void	print(long long time, t_philo *philo, char *str);
long long	time_phi(void);
int	ft_atoi(const char *str);
#endif
