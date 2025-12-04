/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:30:47 by ranhaia-          #+#    #+#             */
/*   Updated: 2025/12/04 15:27:34 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define RED "\033[31m"
# define GREEN "\033[32m"
# define RESET "\033[0m"

typedef struct s_philo_info
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*dead_lock;
	int				num_philos;
	int				time_to_die;	
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_num;
	int				simulation_running;
	struct timeval	start_time;
}	t_philo_info;

typedef struct s_philo
{
	pthread_t		philosopher;
	t_philo_info	*info_table;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	int				has_left_fork;
	int				has_right_fork;
	long long		last_meal_time;
	int				meals_eaten;
	int				philosopher_id;
	struct timeval	start_time;
}		t_philo;

int			ft_atoi(const char *nptr);
int			set_philo_args(t_philo_info *info, int argc, char *argv[]);
int			init_mutexes(t_philo_info *info);
void		destroy_mutexes(t_philo_info *info);
void		assign_forks(t_philo_info *info, t_philo *philosophers);
void		ft_sleep(int milliseconds);
long long	return_time(struct timeval start_time);
long long	time_to_ms(struct timeval time);
int			take_both_forks(t_philo *philos);
void		drop_forks(t_philo *philos);

void		ph_eat(t_philo *philos);
void		ph_sleep(t_philo *philos);
void		ph_think(t_philo *philos);
int			take_left_fork(t_philo *philos);
int			take_right_fork(t_philo *philos);
int			check_phil_death(t_philo *philos);

t_philo		*set_philo_info(t_philo_info *info);

void		create_threads(t_philo_info info, t_philo *philosophers);
void		join_threads(t_philo_info info, t_philo *philosophers);

void		*philo_routine(void *args);
void		*monitor_routine(void *args);

#endif