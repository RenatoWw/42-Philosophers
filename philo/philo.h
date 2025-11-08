/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:30:47 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/11/07 22:08:41 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo {
	pthread_t		philosopher;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	int				philosopher_id;
	int				is_dead;
}		t_philo;

typedef struct s_philo_info {
	pthread_mutex_t	*forks;
	int				num_philos;
	int				time_to_die;	
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_num;
}	t_philo_info;


typedef struct s_table {
	t_philo			*philo;
	t_philo_info	*info;
}	t_table;


int		create_forks(t_philo_info *info);
int		ft_atoi(const char *nptr);
int		set_philo_args(t_philo_info *info, int argc, char *argv[]);
void	destroy_forks(t_philo_info *info);
void	assign_forks(t_philo_info *info, t_philo *philosophers);

#endif