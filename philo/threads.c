/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:01:35 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/11/28 14:40:37 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_philo_info info, t_philo *philosophers)
{
	int		i;

	i = 0;
	while (i < info.num_philos)
	{
		if (pthread_create(&philosophers[i].philosopher, NULL,
				&philo_routine, &philosophers[i]) != 0)
		{
			printf("Error creating philosopher.\n");
			exit(1);
		}
		i++;
	}
}

void	join_threads(t_philo_info info, t_philo *philosophers)
{
	int	i;

	i = 0;
	while (i < info.num_philos)
	{
		if (pthread_join(philosophers[i].philosopher, NULL) != 0)
		{
			printf("Error joining philosopher.\n");
			exit(1);
		}
		i++;
	}
}
