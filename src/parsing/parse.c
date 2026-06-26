/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 14:02:53 by adchebbi          #+#    #+#             */
/*   Updated: 2026/06/26 16:07:25 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_positive_digits(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	parse_one(const char *str, long *out)
{
	long	value;
	int		i;

	if (!is_positive_digits(str))
		return (1);
	value = 0;
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		value = value * 10 + (str[i] - '0');
		if (value > INT_MAX)
			return (1);
		i++;
	}
	*out = value;
	return (0);
}

static int	err(const char *str)
{
	printf("Error : %s\n", str);
	return (1);
}

static int	parse_main_four(char **argv, t_table *table)
{
	long	value;

	if (parse_one(argv[1], &value) || value < 1 || value > 200)
		return (err("nb_philos must be 1..200"));
	table->nb_philos = (int)value;
	if (parse_one(argv[2], &table->time_to_die) || table->time_to_die < 1)
		return (err("bad time_to_die"));
	if (parse_one(argv[3], &table->time_to_eat) || table->time_to_eat < 1)
		return (err("bas time_to_eat"));
	if (parse_one(argv[4], &table->time_to_sleep) || table->time_to_sleep < 1)
		return (err("bad time_to_sleep"));
	return (0);
}

int	parse_args(int argc, char **argv, t_table *table)
{
	long	value;

	if (argc != 5 && argc != 6)
		return (err("Usage : ./philo n t_die t_eat t_sleep [must_sleep]"));
	if (parse_main_four(argv, table))
		return (1);
	table->must_eat_count = -1;
	if (argc == 6)
	{
		if (parse_one(argv[5], &value) || value < 0)
			return (err("bad must_eat"));
		table->must_eat_count = (int)value;
	}
	return (0);
}
