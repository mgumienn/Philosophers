/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 23:45:00 by mgumienn          #+#    #+#             */
/*   Updated: 2025/12/27 14:23:23 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

long long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_error(char *s, int status)
{
	(void)s;
	write(2, "Error\n", 6);
	exit(status);
	return (status);
}

void	print_msg(t_box *box, int id, char *msg)
{
	long long	time;

	pthread_mutex_lock(&box->dead_lock);
	if (box->dead_flag == -1)
	{
		time = get_time() - box->start_time;
		pthread_mutex_lock(&box->write_lock);
		printf("[%lld] %d %s\n", time, id + 1, msg);
		pthread_mutex_unlock(&box->write_lock);
	}
	pthread_mutex_unlock(&box->dead_lock);
}

int	check_death(t_box *box, t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&box->meal_lock);
	time = get_time();
	if ((time - philo->last_meal) > box->die)
	{
		pthread_mutex_unlock(&box->meal_lock);
		print_msg(box, philo->id, "died");
		pthread_mutex_lock(&box->dead_lock);
		box->dead_flag = 1;
		pthread_mutex_unlock(&box->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&box->meal_lock);
	return (0);
}

void	ft_usleep(long long time_in_ms)
{
	long long	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < time_in_ms)
		usleep(1);
}
