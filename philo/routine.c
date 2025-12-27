/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 23:45:00 by mgumienn          #+#    #+#             */
/*   Updated: 2025/12/27 14:10:38 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat_routine(t_philo *philo)
{
	t_box	*box;

	box = philo->box;
	pthread_mutex_lock(&philo->forks[philo->id]);
	print_msg(box, philo->id, "has taken a fork");
	pthread_mutex_lock(&philo->forks[(philo->id + 1) % box->nbr]);
	print_msg(box, philo->id, "has taken a fork");
	print_msg(box, philo->id, "is eating");
	pthread_mutex_lock(&box->meal_lock);
	philo->last_meal = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&box->meal_lock);
	ft_usleep(box->eat);
	pthread_mutex_unlock(&philo->forks[philo->id]);
	pthread_mutex_unlock(&philo->forks[(philo->id + 1) % box->nbr]);
}

int	handle_single_philo(t_philo *philo)
{
	t_box	*box;

	box = philo->box;
	pthread_mutex_lock(&philo->forks[philo->id]);
	print_msg(box, philo->id, "has taken a fork");
	pthread_mutex_unlock(&philo->forks[philo->id]);
	ft_usleep(philo->box->die * 1.1);
	return (1);
}

void	wait_start(t_box *box, t_philo *philo)
{
	while (box->start_time == 0)
		ft_usleep(1);
	pthread_mutex_lock(&box->meal_lock);
	philo->last_meal = box->start_time;
	pthread_mutex_unlock(&box->meal_lock);
}

void	*live_cycle(void *args)
{
	t_philo	*philo;
	t_box	*box;

	philo = (t_philo *)args;
	box = philo->box;
	wait_start(box, philo);
	if (philo->id % 2 == 0)
		ft_usleep(5);
	while (1)
	{
		pthread_mutex_lock(&box->dead_lock);
		if (box->dead_flag != -1)
			return (pthread_mutex_unlock(&box->dead_lock), NULL);
		pthread_mutex_unlock(&box->dead_lock);
		if (box->nbr == 1)
			if (handle_single_philo(philo))
				return (NULL);
		eat_routine(philo);
		print_msg(box, philo->id, "is sleeping");
		ft_usleep(box->sleep);
		print_msg(box, philo->id, "is thinking");
	}
	return (NULL);
}
