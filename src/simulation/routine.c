/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 15:50:12 by adchebbi          #+#    #+#             */
/*   Updated: 2026/06/26 16:05:29 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	action_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_ms = get_time_ms();
	pthread_mutex_unlock(&philo->meal_lock);
	log_action(philo, "is eating");
	precise_sleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_lock(&philo->meal_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
}

static void	action_sleep(t_philo *philo)
{
	log_action(philo, "is sleeping");
	precise_sleep(philo->table->time_to_sleep, philo->table);
}

static void	action_think(t_philo *philo)
{
	long	last_meal_ms;
	long	wait;

	log_action(philo, "is thinking");
	pthread_mutex_lock(&philo->meal_lock);
	last_meal_ms = philo->last_meal_ms;
	pthread_mutex_unlock(&philo->meal_lock);
	wait = philo->table->time_to_die - (get_time_ms() - last_meal_ms)
		- philo->table->time_to_eat;
	if (wait < 0)
		wait = 0;
	if (wait > 200)
		wait = 200;
	if (wait > 0)
		precise_sleep(wait / 2, philo->table);
}

static void	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
	log_action(philo, "has taken a fork");
	precise_sleep(philo->table->time_to_die + 10, philo->table);
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
}

void	*philo_routine(void *argument)
{
	t_philo	*philo;

	philo = (t_philo *)argument;
	if (philo->table->nb_philos == 1)
	{
		handle_single_philo(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		precise_sleep(philo->table->time_to_eat / 2, philo->table);
	while (!should_stop(philo->table))
	{
		take_forks(philo);
		if (should_stop(philo->table))
		{
			drop_forks(philo);
			break ;
		}
		action_eat(philo);
		drop_forks(philo);
		action_sleep(philo);
		action_think(philo);
	}
	return (NULL);
}
