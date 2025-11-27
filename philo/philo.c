/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:53:16 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/11/27 19:36:32 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_phil_death(t_philo *philos)
{
	pthread_mutex_lock(philos->info_table->dead_lock);
	if (philos->info_table->simulation_running == 0)
	{
		pthread_mutex_unlock(philos->info_table->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philos->info_table->dead_lock);
	return (0);
}

void	*routine(void *args)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *) args;
	i = 0;
	if (philos->philosopher_id % 2 == 0)
		usleep(philos->info_table->time_to_eat * 500);
	while (1)
	{
		// criar função check_death
		if (check_phil_death(philos) == 1)
			break ;
		// pthread_mutex_lock(philos->info_table->dead_lock);
		// if (philos->info_table->simulation_running == 0)
		// {
		// 	pthread_mutex_unlock(philos->info_table->dead_lock);
		// 	break ;
		// 	// return (1);
		// }
		pthread_mutex_unlock(philos->info_table->dead_lock);
		ph_eat(philos);
		
		if (check_phil_death(philos) == 1)
			break ;

		ph_sleep(philos);
		
		if (check_phil_death(philos) == 1)
			break ;
		ph_think(philos);
		i++;
	}
	return (NULL);
}

void	*monitor_routine(void *args)
{
	// struct timeval	current_time;
	// long long		time_since_meal;
	t_philo			*philos;
	int				i;

	philos = (t_philo *) args;
	while (1)
	{
		i = 0;
		while (i < philos[0].info_table->num_philos)
		{
			// gettimeofday(&current_time, NULL);
			// printf("oi\n");
			// time_since_meal = return_time(current_time) - philos[i].last_meal_time;
			// pthread_mutex_unlock(philos[i].info_table->meal_lock);
			// pthread_mutex_lock(philos[i].info_table->write_lock);
			// printf("time_since_meal: %lld\n", time_since_meal);
			// ft_sleep(10);
			// pthread_mutex_unlock(philos[i].info_table->write_lock);
			// printf("%d: last_meal_time: %lld\n", time_since_meal);
			// if (time_since_meal > philos[i].info_table->time_to_die)
			// {
			// 	pthread_mutex_lock(philos[i].info_table->dead_lock);
			// 	philos[i].info_table->simulation_running = 0;
			// 	pthread_mutex_unlock(philos[i].info_table->dead_lock);
			// 	pthread_mutex_lock(philos[i].info_table->write_lock);
			// 	printf("%d: %lld\n", philos[i].philosopher_id, philos[i].last_meal_time);
			// 	printf(RED "%d MORREU!!!!!\n" RESET, philos[i].philosopher_id);
			// 	pthread_mutex_unlock(philos[i].info_table->write_lock);
			// 	return (NULL);
			// }
			i++;
		}
		usleep(500);
	}
	return (NULL);
}

// fazer as funções do monitor
// if (last metal time - current_time > info->time_to_die)
// morreu
// é assim??

int	main(int argc, char *argv[])
{	
	t_philo_info	info;
	t_philo			*philosophers;
	// pthread_t		monitor;
	int				i;

	if (set_philo_args(&info, argc, argv) != 0)
		return (1);
	philosophers = set_philo_info(&info);
	if (init_mutexes(&info) != 0)
		return (1); // free e depois return?
	assign_forks(&info, philosophers);
	i = 0;
	// struct timeval current_time;
	// gettimeofday(&current_time, NULL);
	// printf("time: %lld \n", return_time(current_time));
	// ft_sleep(1000);
	// // gettimeofday(&current_time, NULL);
	// printf("time: %lld \n", return_time(current_time));
	create_threads(info, philosophers);
	// pthread_create(&monitor, NULL, &monitor_routine, philosophers);
	// printf("acabou!\n");
	// create_monitor(info, philosophers);
	// printf("simulation: %d\n", info.simulation_running);
	// pthread_join(monitor, NULL);
	join_threads(info, philosophers);
	free(philosophers); // free em cada philosopher?
	destroy_mutexes(&info);
	return (0);
}
