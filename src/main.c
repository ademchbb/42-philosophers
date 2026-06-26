/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 13:38:56 by adchebbi          #+#    #+#             */
/*   Updated: 2026/06/26 16:51:50 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	zero_table(t_table *table)
{
	table->forks = NULL;
	table->philos = NULL;
	table->stop_flag = 0;
	table->launched_count = 0;
}

int	main(int argc, char **argv)
{
	t_table	table;

	zero_table(&table);
	if (parse_args(argc, argv, &table))
		return (1);
	if (init_table(&table))
		return (cleanup(&table), 1);
	if (init_philos(&table))
		return (cleanup(&table), 1);
	if (launch_threads(&table))
		return (cleanup(&table), 1);
	monitor_loop(&table);
	cleanup(&table);
	return (0);
}
