/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 19:34:09 by mgumienn          #+#    #+#             */
/*   Updated: 2025/12/19 20:08:05 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_atol(char *s)
{
	int		i;
	long	n;

	i = 0;
	n = 0;
	while (s[i++])
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (ft_error("Incorrect data", 0), -1);
	i = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		n = n * 10 + (s[i] - 48);
	}
	return (n);
}

int	validate(int argc, char **argv, t_box *box)
{
	box->nbr = ft_atol(argv[1]);
	box->die = ft_atol(argv[2]);
	box->eat = ft_atol(argv[3]);
	box->sleep = ft_atol(argv[4]);
	if (argv[5])
		box->eat_count = ft_atol(argv[5]);
}
