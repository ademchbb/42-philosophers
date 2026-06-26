/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 14:49:29 by adchebbi          #+#    #+#             */
/*   Updated: 2026/06/26 14:52:59 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

void	precise_sleep(long ms, t_table *table)
{
	long	start;

	start = get_time_ms();
	while (get_time_ms() - start < ms)
	{
		if (should_stop(table))
			return ;
		usleep(100);
	}
}
