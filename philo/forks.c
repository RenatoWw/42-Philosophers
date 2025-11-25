/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 22:07:07 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/11/25 18:42:41 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_philo_info *info, t_philo *philosophers)
{
	int	i;

	info->write_lock = malloc(sizeof(pthread_mutex_t) * info->num_philos);
	if (!info->write_lock)
		return (1);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->num_philos);
	if (!info->forks)
		return (1);
	info->meal_lock = malloc(sizeof(pthread_mutex_t) * info->num_philos);
	if (!info->meal_lock)
		return (1);
	i = 0;
	while (i < info->num_philos)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
			return (1);
		if (pthread_mutex_init(&info->write_lock[i], NULL) != 0)
			return (1);
		if (pthread_mutex_init(&info->meal_lock[i], NULL) != 0)
			return (1);
		i++;
	}
	assign_forks(info, philosophers);
	return (0);
}

void	destroy_mutexes(t_philo_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philos)
	{
		pthread_mutex_destroy(&info->forks[i]);
		pthread_mutex_destroy(&info->write_lock[i]);
		pthread_mutex_destroy(&info->meal_lock[i]);
		i++;
	}
	free(info->forks);
	free(info->write_lock); // free em cada info[i]?
	free(info->meal_lock);
}

void	assign_forks(t_philo_info *info, t_philo *philosophers)
{
	int	i;

	i = 0;
	while (i < info->num_philos)
	{
		philosophers[i].left_fork = &info->forks[i];
		philosophers[i].right_fork = &info->forks[i + 1];
		if (i + 1 == info->num_philos)
			philosophers[i].right_fork = &info->forks[0];
		i++;
	}
}

void	ft_print_forks(t_philo_info info, t_philo *philosophers)
{
	int	i;

	i = 0;
	while (i < info.num_philos)
	{
		printf("Fork %d: %p\n", i, &info.forks[i]);
		i++;
	}
	i = 0;
	while (i < info.num_philos)
	{
		printf("Philosopher %d\nLeft fork:  %p\nRight fork: %p\n",
			philosophers[i].philosopher_id,
			philosophers[i].left_fork,
			philosophers[i].right_fork);
		i++;
	}
}
