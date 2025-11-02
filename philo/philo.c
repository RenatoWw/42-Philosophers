/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:53:16 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/11/02 18:32:30 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	num = 0;
pthread_mutex_t mutex;

void	*routine()
{
	int	i;

	i = 0;
	while (i < 10000000)
	{
		pthread_mutex_lock(&mutex);
		num++;
		pthread_mutex_unlock(&mutex);
		i++;
	}
	return (NULL);
}

int	main(void)
{
	pthread_t	thread_1;
	pthread_t	thread_2;

	pthread_mutex_init(&mutex, NULL);
	pthread_create(&thread_1, NULL, &routine, NULL);
	pthread_create(&thread_2, NULL, &routine, NULL);
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
	pthread_mutex_destroy(&mutex);
	printf("num: %d\n", num);
	return (0);
}
