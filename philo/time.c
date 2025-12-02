/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:36:16 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/12/02 14:33:02 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(int milliseconds)
{
	struct timeval	time;
	long long		current_time;
	long long		start_time;

	gettimeofday(&time, NULL);
	start_time = time_to_ms(time);
	while (1)
	{
		gettimeofday(&time, NULL);
		current_time = time_to_ms(time);
		if (current_time - start_time >= milliseconds)
			break ;
		usleep(50);
	}
}

long long	return_time(struct timeval start_time)
{
	struct timeval	current_time;
	long long		current_time_in_mc;
	long long		elapsed_time;

	gettimeofday(&current_time, NULL);
	current_time_in_mc = 1000000 * current_time.tv_sec + current_time.tv_usec;
	elapsed_time = 1000000 * start_time.tv_sec + start_time.tv_usec;
	return (current_time_in_mc / 1000 - elapsed_time / 1000);
}

long long	time_to_ms(struct timeval time)
{
	long long	milliseconds;

	milliseconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (milliseconds);
}
