/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 23:45:00 by mgumienn          #+#    #+#             */
/*   Updated: 2025/12/27 14:07:18 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_all_finished(t_box *box, t_philo *philos)
{
	int	i;
	int	finished;

	i = -1;
	finished = 0;
	while (++i < box->nbr)
	{
		pthread_mutex_lock(&box->meal_lock);
		if (box->eat_count != -1
			&& philos[i].eat_count >= box->eat_count)
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
