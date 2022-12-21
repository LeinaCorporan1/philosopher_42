/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:49:56 by lcorpora          #+#    #+#             */
/*   Updated: 2022/12/21 23:09:11 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_phi(void *philosopher)
{
	t_philo		*philo;

	philo = (t_philo *)philosopher;
	print(0, philo, "has taken a fork", philo->data);
	ft_sleep(philo->data->die, philo->data);
	print(philo->data->die, philo, "died", philo->data);
	return (0);
}

void	eating(void *philosophers)
{
	t_stat	*data;
	t_philo	*philo;

	philo = (t_philo *)philosophers;
	data = philo->data;
	pthread_mutex_lock((philo->r_fork));
	print(time_phi(), philo, "has taken a fork", data);
	pthread_mutex_lock(&(philo->l_fork));
	print(time_phi(), philo, "has taken a fork", data);
	pthread_mutex_lock(&(data -> eating));
	print(time_phi(),philo, "is eating",data);
	pthread_mutex_lock(&(data->must_eat[philo->id -1]));
	philo -> last_meal = time_phi();
	pthread_mutex_unlock(&(data->must_eat[philo->id -1]));
	pthread_mutex_unlock(&(data->eating));
	ft_sleep(data->eat, data);
	pthread_mutex_lock(&(data->must_eat[philo->id -1]));
	philo->x_eat++;
	pthread_mutex_unlock(&(philo->l_fork));
		pthread_mutex_unlock((philo->r_fork));
	pthread_mutex_unlock(&(data->must_eat[philo->id -1]));
}

void	pair_eating(void *philosophers)
{
	t_stat	*data;
	t_philo *philo;

	philo = (t_philo *)philosophers;
	data = philo->data;
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock((philo->r_fork));
		philo->l_fork_taken = 1;
	}
	else
		pthread_mutex_lock(&(philo->l_fork));
	print(time_phi(),philo, "has taken a fork", data);
	if (philo->id % 2 != 0)
		pthread_mutex_lock(&(philo->l_fork));
	else
		pthread_mutex_lock((philo->r_fork));
	print(time_phi(),philo, "has taken a fork", data);
	// pthread_mutex_lock(&(data->eating));
	print(time_phi(),philo, "is eating", data);
	pthread_mutex_lock(&(data->must_eat[philo->id - 1]));
	philo -> last_meal = time_phi();
	philo->x_eat++;
	pthread_mutex_unlock(&(data->must_eat[philo->id - 1]));
	ft_sleep(data->eat, data);
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock((philo->r_fork));
		philo->l_fork_taken = 0;
	}
	else
		pthread_mutex_unlock(&(philo->l_fork));
	if (philo->id % 2 != 0)
		pthread_mutex_unlock(&(philo->l_fork));
	else
	{
		philo->l_fork_taken = 0;
		pthread_mutex_unlock((philo->r_fork));
	}
}

void	wich_eat(t_philo *philo)
{
	//if (philo->data->nb_philo % 2 == 0)
		pair_eating(philo);
	//else
		//eating(philo);

}

void	ft_check_sleep(t_stat *data, t_philo *philo)
{
	long long	normal_duration;
	long long	die_duration;
	long long	sleep_to_die;

	normal_duration = (philo->last_meal + data->eat + data->sleep);
	die_duration = (philo->last_meal + data->die);
	// if (normal_duration > die_duration)
	// {
	// 	printf("duration bigger than die\n");
		ft_sleep(data->sleep, data);
	// }
	// else
	// {
		printf("duration NOT bigger than die\n");
		// sleep_to_die = die_duration - time_phi();
		// ft_sleep(sleep_to_die, data);
		mutex_dead(data, philo);
		pthread_mutex_lock(&(data->dead));
		data->philo_died = 1;
		pthread_mutex_unlock(&(data->dead));
	// }
}

void	ft_check_death_inside_think(t_stat *data, t_philo *philo)
{
	// time to death Death time = 350
	// eat time = 200
	// sleep time = 100

	// think time = ???

	// Eat time = Sleep + (think time)
	
	// unit time = 50

	//				
	// Philo 1 : |EEEE|SST*T|EEEE|...
	// Philo 2 : |TTTT|EEE*E|SSTT|...
	
	
// ############ NORMAL NO DEATH
	// time to death Death time = 380
	// eat time = 200
	// sleep time = 100

	// think time = 100 (eat time - think time)

	// (Eat time == Sleep + (think time)

	// die_duration T : 380 ms
	
	long long	think_time;
	long long	normal_duration;
	long long	die_duration;
	long long	sleep_to_die;
	// printf("\nThinking ");
	print(time_phi(), philo, "is thinking",data);
	if (data->eat > data->sleep)
	{
		think_time = data->eat - data->sleep; // 100 
		normal_duration = philo->last_meal + data->eat + data->sleep + think_time;
		die_duration = (philo->last_meal + data->die);
		sleep_to_die = die_duration - time_phi();
		
		if (normal_duration > die_duration)
		{
			usleep(sleep_to_die);

			// ###### NEED TO PRINT DEATH remplace with mutex dead
			mutex_dead(data, philo);
			pthread_mutex_lock(&(data->dead));
			data->philo_died = 1;
			pthread_mutex_unlock(&(data->dead));
		}
	}
}

void	*routine(void *philosophers)
{
	t_philo		*philo;
	t_stat		*data;

	philo = (t_philo *)philosophers;
	data = philo->data;
	if (philo -> id % 2 == 0)
		usleep(200);
	while (check_data_died(data) == 0 && data_all_eat1(data) == 0)
	{
		// wich_eat(philo);
		pair_eating(philo);
		
		if (check_nb_eat(data) == 1)
		{
			break ;
		}
		print(time_phi(), philo, "is sleeping",data);
		if (check_data_died(data)== 0)
		{
			ft_sleep(data->sleep, data);
			// ft_check_sleep(data, philo);
			// if (check_data_died(data)!= 0)
			// return (NULL);
		}
		else
			ft_sleep(data->die, data);
			
		if (check_nb_eat(data) == 1)
		{
			break ;
		}
		// print(time_phi(), philo, "is thinking",data);
		// usleep(100);
		//ft_check_death_inside_think(data, philo);
		// usleep((data->die - (philo->last_meal -
		// 			time_phi()) - data ->eat) / 2);
		usleep(200);
	}
	return (NULL);
}