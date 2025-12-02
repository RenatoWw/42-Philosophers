/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:50:39 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/12/02 20:41:12 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_eat(t_philo *philos)
{
	struct timeval	last_meal;

	if (check_phil_death(philos) == 1)
	{
		return ;
	}
	gettimeofday(&last_meal, NULL);
	pthread_mutex_lock(philos->info_table->meal_lock);
	philos->last_meal_time = time_to_ms(last_meal);
	philos->meals_eaten++;
	pthread_mutex_unlock(philos->info_table->meal_lock);
	pthread_mutex_lock(philos->info_table->write_lock);
	printf("%lld ", return_time(philos->start_time));
	printf(GREEN "%d is eating\n" RESET, philos->philosopher_id);
	pthread_mutex_unlock(philos->info_table->write_lock);
	ft_sleep(philos->info_table->time_to_eat);
	pthread_mutex_unlock(philos->left_fork);
	pthread_mutex_unlock(philos->right_fork);
	philos->has_left_fork = 0;
	philos->has_right_fork = 0;
}

void	ph_sleep(t_philo *philos)
{
	if (check_phil_death(philos) == 1)
		return ;
	pthread_mutex_lock(philos->info_table->write_lock);
	printf("%lld ", return_time(philos->info_table->start_time));
	printf(GREEN "%d is sleeping\n" RESET, philos->philosopher_id);
	pthread_mutex_unlock(philos->info_table->write_lock);
	ft_sleep(philos->info_table->time_to_sleep);
}

void	ph_think(t_philo *philos)
{
	if (check_phil_death(philos) == 1)
		return ;
	pthread_mutex_lock(philos->info_table->write_lock);
	printf("%lld ", return_time(philos->info_table->start_time));
	printf(GREEN "%d is thinking\n" RESET, philos->philosopher_id);
	pthread_mutex_unlock(philos->info_table->write_lock);
}

int	take_left_fork(t_philo *philos)
{
	pthread_mutex_lock(philos->left_fork);
	philos->has_left_fork = 1;
	if (check_phil_death(philos) == 1)
	{
		philos->has_left_fork = 0;
		pthread_mutex_unlock(philos->left_fork);
		return (0);
	}
	pthread_mutex_lock(philos->info_table->write_lock);
	printf("%lld ", return_time(philos->info_table->start_time));
	printf(GREEN "%d has taken a fork\n" RESET, philos->philosopher_id);
	pthread_mutex_unlock(philos->info_table->write_lock);
	return (1);
}

int	take_right_fork(t_philo *philos)
{
	pthread_mutex_lock(philos->right_fork);
	philos->has_right_fork = 1;
	if (check_phil_death(philos) == 1)
	{
		philos->has_right_fork = 0;
		pthread_mutex_unlock(philos->right_fork);
		return (0);
	}
	pthread_mutex_lock(philos->info_table->write_lock);
	printf("%lld ", return_time(philos->info_table->start_time));
	printf(GREEN "%d has taken a fork\n" RESET, philos->philosopher_id);
	pthread_mutex_unlock(philos->info_table->write_lock);
	return (1);
}
