/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 23:45:00 by mgumienn          #+#    #+#             */
/*   Updated: 2025/12/27 14:30:00 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_start_time(t_philo *philo, t_box *box)
{
	int	i;

	box->start_time = get_time();
	i = -1;
	while (++i < box->nbr)
		philo[i].last_meal = box->start_time;
}

void	join_threads(pthread_t *threads, t_box *box)
{
	int	i;

	i = -1;
	while (++i < box->nbr)
		pthread_join(threads[i], NULL);
}

int	create_threads(t_box *box)
{
	pthread_t	*threads;
	t_philo		*philo;

	threads = malloc(box->nbr * sizeof(pthread_t));
	philo = malloc(box->nbr * sizeof(t_philo));
	if (!threads || !philo)
		return (ft_error("Malloc failed", 1));
	init_mutexes(box);
	box->start_time = 0;
	if (create_philo_threads(threads, philo, box))
	{
		free(threads);
		free(philo);
		return (ft_error("Threads error", 1));
	}
	set_start_time(philo, box);
	ft_monitor(box, philo);
	join_threads(threads, box);
	free(threads);
	free(philo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_box	box;

	if (argc < 5)
		return (ft_error("Args error", 1));
	if (validate(argc, argv, &box) == 0)
		return (ft_error("No philosophers", 1));
	if (box.nbr == 0)
		return (0);
	box.forks = malloc(box.nbr * sizeof(pthread_mutex_t));
	if (!box.forks)
		return (ft_error("Malloc failed", 1));
	create_threads(&box);
	free(box.forks);
	return (0);
}
