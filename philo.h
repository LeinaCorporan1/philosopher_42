#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>

typedef struct s_stat
{
	int	eat;
	int	sleep;
	int	think;
	int	nb_philo;
	int	m_eat;
	pthread_t	philo;
}
