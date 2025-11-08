/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 22:07:07 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/11/07 22:07:30 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_forks(t_philo_info *info)
{
	int	i;

	info->forks = malloc(sizeof(pthread_mutex_t) * info->num_philos);
	if (!info->forks)
		return (1);
	i = 0;
	while (i < info->num_philos)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
			// free/destroy mutexes and return 1
			return (1);
		i++;
	}
	return (0);
}

void	destroy_forks(t_philo_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philos)
	{
		pthread_mutex_destroy(&info->forks[i]);
		i++;
	}
	free(info->forks);
}

void	assign_forks(t_philo_info *info, t_philo *philosophers)
{
	int	i;

	i = 0;
	philosophers[0].left_fork = &info->forks[0];
	philosophers[0].right_fork = &info->forks[1];

	philosophers[1].left_fork = &info->forks[1];
	philosophers[1].right_fork = &info->forks[2];
	while (i < info->num_philos)
	{
		philosophers[i].left_fork = &info->forks[i];
		philosophers[i].right_fork = &info->forks[i + 1];
		if (i + 1 == info->num_philos)
			philosophers[i].right_fork = &info->forks[0];
		i++;
	}
}
