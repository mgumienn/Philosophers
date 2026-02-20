/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 23:45:00 by mgumienn          #+#    #+#             */
/*   Updated: 2026/02/01 12:42:43 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_mutexes(t_box *box)
{
	int	i;

	pthread_mutex_init(&box->write_lock, NULL);
	pthread_mutex_init(&box->dead_lock, NULL);
	pthread_mutex_init(&box->meal_lock, NULL);
	pthread_mutex_init(&box->start_lock, NULL);
	i = -1;
	while (++i < box->nbr)
		pthread_mutex_init(&box->forks[i], NULL);
}

void	init_philo(t_philo *philo, t_box *box, int id)
{
	philo->id = id;
	philo->box = box;
	philo->forks = box->forks;
	philo->eat_count = 0;
	philo->last_meal = 0;
}

int	create_philo_threads(pthread_t *threads, t_philo *philo, t_box *box)
{
	int	i;

	i = -1;
	while (++i < box->nbr)
	{
		init_philo(&philo[i], box, i);
		if (pthread_create(&threads[i], NULL, &live_cycle, &philo[i]) != 0)
			return (1);
	}
	return (0);
}
