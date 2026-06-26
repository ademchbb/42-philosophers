/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 15:42:19 by adchebbi          #+#    #+#             */
/*   Updated: 2026/06/26 15:49:37 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_one_philo(t_philo *philo, long now)
{
	long	elapsed;

	pthread_mutex_lock(&philo->meal_lock);
	elapsed = now - philo->last_meal_ms;
	pthread_mutex_unlock(&philo->meal_lock);
	if (elapsed > philo->table->time_to_die)
	{
		set_stop(philo->table);
		log_death(philo);
		return (1);
	}
	return (0);
}

static int	all_full(t_table *table)
{
	int	i;
	int	full;

	if (table->must_eat_count < 0)
		return (0);
	i = 0;
	full = 1;
	while (i < table->nb_philos)
	{
		pthread_mutex_lock(&table->philos[i].meal_lock);
		if (table->philos[i].meals_eaten < table->must_eat_count)
			full = 0;
		pthread_mutex_unlock(&table->philos[i].meal_lock);
		i++;
	}
	return (full);
}

void	monitor_loop(t_table *table)
{
	int		i;
	long	now;

	while (!should_stop(table))
	{
		now = get_time_ms();
		i = 0;
		while (i < table->nb_philos)
		{
			if (check_one_philo(&table->philos[i], now))
				return ;
			i++;
		}
		if (all_full(table))
		{
			set_stop(table);
			return ;
		}
		usleep(500);
	}
}
