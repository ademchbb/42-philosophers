/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 14:30:36 by adchebbi          #+#    #+#             */
/*   Updated: 2026/06/26 14:48:16 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

int	init_table(t_table *table)
{
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philos);
	if (!table->forks)
		return (1);
	table->philos = malloc(sizeof(t_philo) * table->nb_philos);
	if (!table->philos)
		return (1);
	memset(table->philos, 0, sizeof(t_philo) * table->nb_philos);
	if (pthread_mutex_init(&table->print_lock, NULL))
		return (1);
	if (pthread_mutex_init(&table->state_lock, NULL))
		return (1);
	if (init_forks(table))
		return (1);
	return (0);
}

int	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal_ms = 0;
		table->philos[i].left_fork = i;
		table->philos[i].right_fork = (i + 1) % table->nb_philos;
		table->philos[i].table = table;
		if (pthread_mutex_init(&table->philos[i].meal_lock, NULL))
			return (1);
		i++;
	}
	return (0);
}

int	launch_threads(t_table *table)
{
	int	i;

	table->start_time_ms = get_time_ms();
	table->launched_count = 0;
	i = 0;
	while (i < table->nb_philos)
	{
		table->philos[i].last_meal_ms = table->start_time_ms;
		if (pthread_create(&table->philos[i].thread, NULL,
				philo_routine, &table->philos[i]))
		{
			set_stop(table);
			return (1);
		}
		table->launched_count++;
		i++;
	}
	return (0);
}
