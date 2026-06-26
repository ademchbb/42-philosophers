/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 15:34:34 by adchebbi          #+#    #+#             */
/*   Updated: 2026/06/26 16:08:27 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_pair(t_philo *philo, int first, int second)
{
	pthread_mutex_lock(&philo->table->forks[first]);
	log_action(philo, "has taken a fork");
	pthread_mutex_lock(&philo->table->forks[second]);
	log_action(philo, "has taken a fork");
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		lock_pair(philo, philo->right_fork, philo->left_fork);
	else
		lock_pair(philo, philo->left_fork, philo->right_fork);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
}
