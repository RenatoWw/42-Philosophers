/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 22:08:09 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/11/07 22:08:44 by ranhaia-         ###   ########.fr       */
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

int	set_philo_args(t_philo_info *info, int argc, char *argv[])
{
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
