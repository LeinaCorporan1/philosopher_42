/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 04:22:29 by lcorpora          #+#    #+#             */
/*   Updated: 2023/01/27 10:59:26 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	l_fork;
	int				taken_l;
	int				taken_r;
	pthread_mutex_t	m_philo;
	int				id;
	int				as_eaten;
	long long		last_meal;
	struct s_stat	*data;
	pthread_t		phi;
}	t_philo;

typedef struct s_stat
{
	long long		eat;
	long long		sleep;
	long long		think;
	long long		nb_philo;
	long long		m_eat;
	long long		die;
	long long		philo_died;
	long long		time_start;
	long long		all_ate;
	pthread_mutex_t	dead;
	pthread_mutex_t	print;
}	t_stat;

int			init_stat(char **av, t_stat *data);
int			init_philo(t_philo **philo, t_stat *data);
void		ft_usleep(long long time_info, t_stat *data);
void		print(long long time, t_philo *philo, char *str);
long long	time_phi(void);
int			ft_atoi(const char *str);
int			check_data_died(t_stat *data);
int			check_nb_eat(t_stat *data, t_philo *philo);
void		ft_monitoring(t_stat *data, t_philo *philo);
int			check_args(char **av);
void		ft_error(char *str);
size_t		ft_strlen(char *c);
void		*routine(void *philosophers);
#endif
