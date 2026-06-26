/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 15:27:34 by adchebbi          #+#    #+#             */
/*   Updated: 2026/06/26 15:33:48 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_action(t_philo *philo, const char *message)
{
	long	timestamp;

	pthread_mutex_lock(&philo->table->print_lock);
	if (!should_stop(philo->table))
	{
		timestamp = get_time_ms() - philo->table->start_time_ms;
		printf("%ld %d %s\n", timestamp, philo->id, message);
	}
	pthread_mutex_unlock(&philo->table->print_lock);
}

void	log_death(t_philo *philo)
{
	long	timestamp;

	pthread_mutex_lock(&philo->table->print_lock);
	timestamp = get_time_ms() - philo->table->start_time_ms;
	printf("%ld %d died\n", timestamp, philo->id);
	pthread_mutex_unlock(&philo->table->print_lock);
}
