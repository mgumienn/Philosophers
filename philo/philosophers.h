/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 19:06:08 by mgumienn          #+#    #+#             */
/*   Updated: 2026/02/01 12:42:43 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_box
{
	int				nbr;
	long long		die;
	long long		eat;
	long long		sleep;
	int				eat_count;
	int				dead_flag;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	start_lock;
}	t_box;

typedef struct s_philo
{
	int				id;
	long long		last_meal;
	int				eat_count;
	pthread_mutex_t	*forks;
	t_box			*box;
}	t_philo;

int			ft_error(char *s, int status);
int			validate(int argc, char **argv, t_box *box);
long long	get_time(void);
void		print_msg(t_box *box, int id, char *msg);
int			check_death(t_box *box, t_philo *philo);
void		ft_monitor(t_box *box, t_philo *philos);
void		*live_cycle(void *args);
void		eat_routine(t_philo *philo);
void		init_mutexes(t_box *box);
int			create_philo_threads(pthread_t *threads, t_philo *philo,
				t_box *box);
void		ft_usleep(long long time_in_ms);

#endif