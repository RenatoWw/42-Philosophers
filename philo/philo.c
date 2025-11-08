/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:53:16 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/11/07 22:16:27 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *args)
{
	t_philo_info	info;
	int				i;

	info = *(t_philo_info *) args;
	i = 0;
	while (i < info.num_philos)
	{
		printf("oi\n");
		i++;
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_philo_info	info;
	t_philo			*philosophers;
	int				i;

	if (set_philo_args(&info, argc, argv) != 0)
		return (1);
	// printf("num_philos: %d\n", info.num_philos);
	philosophers = malloc(sizeof(t_philo) * info.num_philos);
	if (!philosophers)
		return (1);
	i = 0;
	while (i < info.num_philos)
	{
		philosophers[i].philosopher_id = i + 1;
		philosophers[i].is_dead = 0;
		i++;
	}
	create_forks(&info);
	i = 0;
	while (i < info.num_philos)
	{
		printf("Fork %d: %p\n", i, &info.forks[i]);
		i++;
	}
	assign_forks(&info, philosophers);
	i = 0;
	while (i < info.num_philos)
	{
		printf("Philosopher %d\nLeft fork:  %p\nRight fork: %p\n", philosophers[i].philosopher_id, philosophers[i].left_fork, philosophers[i].right_fork);
		i++;
	}
	i = 0;
	while (i < info.num_philos)
	{
		if (pthread_create(&philosophers->philosopher, NULL, &routine, &info) != 0)
		{
			printf("Error creating philosopher.\n");
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < info.num_philos)
	{
		if (pthread_join(philosophers->philosopher, NULL) != 0)
		{
			printf("Error ending philosopher.\n");
			return (1);
		}
		i++;
	}
	free(philosophers);
	destroy_forks(&info);
	return (0);
}
