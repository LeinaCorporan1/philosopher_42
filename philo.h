#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef	struct s_philo
{
	int	fork;
	int	id;
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
