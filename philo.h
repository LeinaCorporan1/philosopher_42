#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef	struct s_philo
{
	int r_fork;
	int l_fork;
	int	id;
	struct s_stat	*data;
	pthread_t phi;
} t_philo;

typedef struct s_stat
{
	int	eat;
	int	sleep;
	int	think;
	int	nb_philo;
	int	m_eat;
	int	die;
	t_philo	*philo;
	pthread_mutex_t *fork;
}	t_stat;

#endif
