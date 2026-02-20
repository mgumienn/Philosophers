/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 23:45:00 by mgumienn          #+#    #+#             */
/*   Updated: 2026/02/01 13:26:48 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_all_finished(t_box *box, t_philo *philos)
{
	int	i;
	int	finished;
	int	eat_count;

	i = -1;
	finished = 0;
	pthread_mutex_lock(&box->meal_lock);
	eat_count = box->eat_count;
	pthread_mutex_unlock(&box->meal_lock);
	while (++i < box->nbr)
	{
		pthread_mutex_lock(&box->meal_lock);
		if (eat_count != -1 && philos[i].eat_count >= eat_count)
			finished++;
		pthread_mutex_unlock(&box->meal_lock);
	}
	return (finished == box->nbr);
}

void	ft_monitor(t_box *box, t_philo *philos)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < box->nbr)
		{
			if (check_death(box, &philos[i]))
				return ;
		}
		pthread_mutex_lock(&box->dead_lock);
		if (box->dead_flag != -1 || check_all_finished(box, philos))
		{
			box->dead_flag = 1;
			pthread_mutex_unlock(&box->dead_lock);
			return ;
		}
		pthread_mutex_unlock(&box->dead_lock);
		ft_usleep(5);
	}
}
