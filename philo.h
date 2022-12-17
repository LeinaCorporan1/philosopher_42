#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

typedef	struct s_philo
{
	int	r_fork;
	int	l_fork;
	int	id;
	int	is_dead;
	int	as_eaten;
	struct s_stat	*data;
	pthread_t phi;
} t_philo;

typedef struct s_stat
{
	long long	eat;
	long long	sleep;
	long long	think;
	long long	nb_philo;
	long long	m_eat;
	long long	die;
	long long	philo_died;
	long long	act_time;
	t_philo	*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
}	t_stat;

#endif
