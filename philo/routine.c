/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:50:39 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/11/27 18:32:09 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_eat(t_philo *philos)
{
	struct timeval	last_meal;

	take_both_forks(philos);
	gettimeofday(&last_meal, NULL);
	pthread_mutex_lock(philos->info_table->meal_lock);
	printf("last meal time: %lld \n", return_time(philos->start_time));
	philos->last_meal_time = return_time(last_meal);
	philos->meals_eaten++;
	pthread_mutex_unlock(philos->info_table->meal_lock);
	pthread_mutex_lock(philos->info_table->write_lock);
	printf("%lld ", return_time(philos->start_time));
	printf(GREEN "Philo %d is eating\n" RESET, philos->philosopher_id);
	pthread_mutex_unlock(philos->info_table->write_lock);
	ft_sleep(philos->info_table->time_to_eat);
	pthread_mutex_unlock(philos->left_fork);
	pthread_mutex_unlock(philos->right_fork);
}

void	ph_sleep(t_philo *philos)
{
	pthread_mutex_lock(philos->info_table->write_lock);
	printf("%lld ", return_time(philos->info_table->start_time));
	printf(GREEN "Philo %d is sleeping\n" RESET, philos->philosopher_id);
	pthread_mutex_unlock(philos->info_table->write_lock);
	ft_sleep(philos->info_table->time_to_sleep);
}

void	ph_think(t_philo *philos)
{
	pthread_mutex_lock(philos->info_table->write_lock);
	printf("%lld ", return_time(philos->info_table->start_time));
	printf(GREEN "Philo %d is thinking\n" RESET, philos->philosopher_id);
	pthread_mutex_unlock(philos->info_table->write_lock);
}

void	take_both_forks(t_philo *philos)
{
	pthread_mutex_lock(philos->left_fork);
	pthread_mutex_lock(philos->info_table->write_lock);
	printf("%lld ", return_time(philos->info_table->start_time));
	printf(GREEN "Philo %d has taken a fork.\n" RESET, philos->philosopher_id);
	pthread_mutex_unlock(philos->info_table->write_lock);
	pthread_mutex_lock(philos->right_fork);
	pthread_mutex_lock(philos->info_table->write_lock);
	printf("%lld ", return_time(philos->info_table->start_time));
	printf(GREEN "Philo %d has taken a fork.\n" RESET, philos->philosopher_id);
	pthread_mutex_unlock(philos->info_table->write_lock);
}
