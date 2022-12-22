/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 19:03:42 by lcorpora          #+#    #+#             */
/*   Updated: 2022/12/22 03:38:28 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
	int				r_fork;
	int				l_fork;
	int				id;
	int				is_dead;
	long long		last_meal;
	long long		x_eat;
	long long		all_eat;
	struct s_stat	*data;
	pthread_mutex_t	m_philo;
	pthread_t		phi;
}	t_philo;

typedef struct s_stat
{
	long long		eat;
	long long		sleep;
	long long		nb_philo;
	long long		m_eat;
	long long		die;
	long long		philo_died;
	long long		time_start;
	long long		all_ate;
	t_philo			philo[200];
	pthread_mutex_t	fork[200];
	pthread_mutex_t	dead;
	pthread_mutex_t	print;
}	t_stat;

int			init_stat(char **av, t_stat *data);
int			init_philo(t_philo *philo, t_stat *data);
void		ft_usleep(long long time_info, long long begin);
void		print(long long time, t_philo *philo, char *str, t_stat *data);
long long	time_phi(void);
int			ft_atoi(const char *str);
int			check_data_died(t_stat *data);
void		*found(void *philosophers);
void		ft_sleep(long long time_to, t_stat *data);
int			check_die_philo(t_stat *data);
void		ft_error(char *str);
void		*routine(void *philosophers);
int			check_nb_eat(t_stat *data);
void		finish_all_mutex(t_stat *data, t_philo *philo);
void		exit_mutex(t_stat *data);
int			check_args(char **av, int ac);
void		death_checker(t_stat *data, t_philo *philo);
int			data_all_eat1(t_stat *data);
void		exit_mutex(t_stat *data);
int			mutex_dead(t_stat *data, t_philo *philo);
size_t		ft_strlen(char *c);
#endif
