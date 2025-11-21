/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:53:16 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/11/21 18:20:01 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *args)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *) args;
	i = 0;
	printf("num_philos: %d\n", philos->num_philos);
	// while (i < table.info->num_philos)
	// {
	// 	printf("Philosopher: %d\n", table.philo->philosopher_id);
	// 	printf("i: %d\n", i);
	// 	i++;
	// }
	return (NULL);
}

void	ft_sleep(int milliseconds)
{
	usleep(milliseconds * 1000);
}

void	ft_print_time(struct timeval start_time)
{
	struct timeval	current_time;
	unsigned long	current_time_in_mc;
	unsigned long	elapsed_time;

	gettimeofday(&current_time, NULL);
	current_time_in_mc = 1000000 * current_time.tv_sec + current_time.tv_usec;
	elapsed_time = 1000000 * start_time.tv_sec + start_time.tv_usec;
	printf("%ld\n", current_time_in_mc / 1000 - elapsed_time / 1000);
}

void	set_philo_info(t_philo *philosophers, t_philo_info *info)
{
	struct timeval start_time;
	int				i;

	i = 0;
	gettimeofday(&start_time, NULL);
	while (i < info->num_philos)
	{
		philosophers[i].philosopher_id = i + 1;
		philosophers[i].is_dead = 0;
		philosophers[i].meals_eaten = 0;
		philosophers[i].start_time = start_time;
		philosophers[i].meals_num = info->meals_num;
		philosophers[i].num_philos = info->num_philos;
		philosophers[i].time_to_die = info->time_to_die;
		philosophers[i].time_to_eat = info->time_to_eat;
		philosophers[i].time_to_sleep = info->time_to_sleep;
		i++;
	}
	if (create_forks(info) == 1)
	{
		printf("Error creating Fork.");
		destroy_forks(info);
		exit(1);
	}
	assign_forks(info, philosophers);
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

void	create_threads(t_philo_info info, t_philo *philosophers)
{
	int	i;

	i = 0;
	while (i < info.num_philos)
	{
		if (pthread_create(&philosophers[i].philosopher, NULL, &routine, &philosophers) != 0)
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

int	main(int argc, char *argv[])
{
	t_philo_info	info;
	t_philo			*philosophers;
	// int				i;

	if (set_philo_args(&info, argc, argv) != 0)
		return (1);
	ft_print_time(info.start_time);
	ft_sleep(info.time_to_die);
	ft_print_time(info.start_time);
	philosophers = malloc(sizeof(t_philo) * info.num_philos);
	if (!philosophers)
		return (1);
	set_philo_info(philosophers, &info);
	// ft_print_forks(info, philosophers);
	// pthread_create(&philosophers[i].philosopher, NULL, &routine, &philosophers);
	// create_threads(info, philosophers);
	// join_threads(info, philosophers);
	free(philosophers);
	destroy_forks(&info);
	return (0);
}
