/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 16:08:58 by adchebbi          #+#    #+#             */
/*   Updated: 2026/06/26 16:13:31 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_all(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->launched_count)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
}

static void	destroy_all(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philos[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->state_lock);
}

void	cleanup(t_table *table)
{
	if (table->launched_count > 0)
		join_all(table);
	if (table->forks && table->philos)
		destroy_all(table);
	free(table->forks);
	free(table->philos);
	table->forks = NULL;
	table->philos = NULL;
}
