/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 13:22:26 by adchebbi          #+#    #+#             */
/*   Updated: 2026/06/26 14:52:30 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <stdlib.h>

typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_ms;
	pthread_mutex_t	meal_lock;
	int				left_fork;
	int				right_fork;
	pthread_t		thread;
	t_table			*table;
};

struct s_table
{
	int				nb_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_count;
	long			start_time_ms;
	int				stop_flag;
	int				launched_count;
	pthread_mutex_t	state_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
};

/*parse.c*/
int		parse_args(int argc, char **argv, t_table *table);

/*init.c*/
int		init_table(t_table *table);
int		init_philos(t_table *table);
int		launch_threads(t_table *table);

/*routine.c*/
void	*philo_routine(void *argument);

/*forks.c*/
void	take_forks(t_philo *philo);
void	drop_forks(t_philo *philo);

/*monitor.c*/
void	monitor_loop(t_table *table);

/*log.c*/
void	log_action(t_philo *philo, const char *message);
void	log_death(t_philo *philo);

/*time.c*/
long	get_time_ms(void);
void	precise_sleep(long ms, t_table *table);

/*state.c*/
int		should_stop(t_table *table);
void	set_stop(t_table *table);

/*cleanup.c*/
void	cleanup(t_table *table);

#endif
