/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:53:16 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/11/28 16:38:55 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *args)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *) args;
	i = 0;
	if (philos->philosopher_id % 2 == 0)
		usleep(philos->info_table->time_to_eat * 500);
	while (1)
	{
		ph_eat(philos);
		if (check_phil_death(philos) == 1)
			break ;
		ph_sleep(philos);
		if (check_phil_death(philos) == 1)
			break ;
		ph_think(philos);
		if (check_phil_death(philos) == 1)
			break ;
		i++;
	}
	return (NULL);
}

int	is_philos_satisfied(t_philo *philos)
{
	int	i;

	pthread_mutex_lock(philos->info_table->meal_lock);
	i = 0;
	while (i < philos->info_table->num_philos)
	{
		if (philos[i].meals_eaten != philos->info_table->meals_num)
		{
			pthread_mutex_unlock(philos->info_table->meal_lock);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(philos->info_table->meal_lock);
	pthread_mutex_lock(philos->info_table->write_lock);
	printf(GREEN "All philosophers finished eating.\n" RESET);
	pthread_mutex_unlock(philos->info_table->write_lock);
	pthread_mutex_lock(philos->info_table->dead_lock);
	philos->info_table->simulation_running = 0;
	pthread_mutex_unlock(philos->info_table->dead_lock);
	return (1);
}

int	is_philos_dead(t_philo *philos, int id)
{
	struct timeval	current_time;
	long long		time_since_meal;

	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(philos->info_table->meal_lock);
	time_since_meal = time_to_ms(current_time) - philos[id].last_meal_time;
	pthread_mutex_unlock(philos->info_table->meal_lock);
	if (time_since_meal > philos->info_table->time_to_die)
	{
		pthread_mutex_lock(philos->info_table->dead_lock);
		philos->info_table->simulation_running = 0;
		pthread_mutex_unlock(philos->info_table->dead_lock);
		pthread_mutex_lock(philos->info_table->write_lock);
		printf("%d: %lld\n", philos[id].philosopher_id,
			time_to_ms(current_time) - philos[id].last_meal_time);
		printf("%lld ", return_time(philos->start_time));
		printf(RED "%d died\n" RESET, philos[id].philosopher_id);
		pthread_mutex_unlock(philos->info_table->write_lock);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *args)
{
	t_philo			*philos;
	int				i;

	philos = (t_philo *) args;
	while (1)
	{
		i = 0;
		while (i < philos[0].info_table->num_philos)
		{
			if (is_philos_dead(philos, i) == 1)
				return (NULL);
			if (is_philos_satisfied(philos) == 1)
				return (NULL);
			i++;
		}
		usleep(500);
	}
	return (NULL);
}

// arrumar is_philos_satisfied - só funciona com 2 por agora
// arrumar erros do helgrind - aparentemente não tem memory leak

int	main(int argc, char *argv[])
{	
	t_philo_info	info;
	t_philo			*philosophers;
	pthread_t		monitor;

	if (set_philo_args(&info, argc, argv) != 0)
		return (1);
	if (init_mutexes(&info) != 0)
		return (1);
	philosophers = set_philo_info(&info);
	assign_forks(&info, philosophers);
	create_threads(info, philosophers);
	pthread_create(&monitor, NULL, &monitor_routine, philosophers);
	pthread_join(monitor, NULL);
	printf("meals_num: %d\n", info.meals_num);
	join_threads(info, philosophers);
	free(philosophers);
	destroy_mutexes(&info);
	return (0);
}
