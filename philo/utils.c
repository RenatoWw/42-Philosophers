/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 22:08:09 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/11/25 18:43:22 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	signal;
	int	num;

	signal = 1;
	num = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			signal *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		num = (num * 10) + *nptr++ - '0';
	}
	return (num * signal);
}

t_philo	*set_philo_info(t_philo_info *info)
{
	struct timeval	start_time;
	t_philo			*philosophers;
	int				i;

	philosophers = malloc(sizeof(t_philo) * info->num_philos);
	if (!philosophers)
		return (NULL);
	i = 0;
	gettimeofday(&start_time, NULL);
	while (i < info->num_philos)
	{
		philosophers[i].philosopher_id = i + 1;
		philosophers[i].is_dead = 0;
		philosophers[i].meals_eaten = 0;
		philosophers[i].start_time = start_time;
		philosophers[i].info_table = info;
		i++;
	}
	return (philosophers);
}

int	set_philo_args(t_philo_info *info, int argc, char *argv[])
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	info->start_time = start_time;
	if (argc != 5 && argc != 6)
		return (1);
	info->num_philos = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->meals_num = ft_atoi(argv[5]);
	else
		info->meals_num = 2147483647;
	return (0);
}
