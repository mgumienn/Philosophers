/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 19:04:01 by mateusz           #+#    #+#             */
/*   Updated: 2025/12/19 19:51:07 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_error(char *s, int status)
{
	write(2, "Error\n", 6);
	while (s++)
		write(2, &s, 1);
	exit(status);
	return (status);
}

int	main(int argc, char **argv)
{
	t_box	box;

	if (argc < 5)
		return (ft_error("Not enough arguments were give", 0));
	validate(argc, argv);
}
