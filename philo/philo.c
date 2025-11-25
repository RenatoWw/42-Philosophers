/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:53:16 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/11/25 18:55:10 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *args)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *) args;
	i = 0;
	while (1)
	{
		if (philos->philosopher_id % 2 == 0)
			usleep(philos->info_table->time_to_eat * 500);
		take_left_fork(philos);
		take_right_fork(philos);
		ph_eat(philos);
		ph_sleep(philos);
		ph_think(philos);
		if (philos->meals_eaten == philos->info_table->meals_num)
		{
			printf(GREEN "All philosophers finished eating.\n" RESET);
			exit(1);
		}
		i++;
	}
	return (NULL);
}

void	create_threads(t_philo_info info, t_philo *philosophers)
{
	int		i;

	i = 0;
	while (i < info.num_philos)
	{
		if (pthread_create(&philosophers[i].philosopher, NULL,
				&routine, &philosophers[i]) != 0)
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

void	monitor_routine(void *args)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *) args;
	while (1)
	{
		i = 0;
		while (i < philos->info_table->num_philos)
		{
		}
	}
}

int	main(int argc, char *argv[])
{	
	t_philo_info	info;
	t_philo			*philosophers;
	int				i;

	if (set_philo_args(&info, argc, argv) != 0)
		return (1);
	philosophers = set_philo_info(&info);
	if (init_mutexes(&info, philosophers) != 0)
		return (1); // free e depois return?
	i = 0;
	create_threads(info, philosophers);
	// create_monitor(info, philosophers);
	join_threads(info, philosophers);
	free(philosophers); // free em cada philosopher?
	destroy_mutexes(&info);
	return (0);
}
