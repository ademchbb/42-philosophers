/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 14:54:28 by adchebbi          #+#    #+#             */
/*   Updated: 2026/06/26 14:59:50 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_stop(t_table *table)
{
	int	value;

	pthread_mutex_lock(&table->state_lock);
	value = table->stop_flag;
	pthread_mutex_unlock(&table->state_lock);
	return (value);
}

void	set_stop(t_table *table)
{
	pthread_mutex_lock(&table->state_lock);
	table->stop_flag = 1;
	pthread_mutex_unlock(&table->state_lock);
}
