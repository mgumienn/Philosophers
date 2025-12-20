/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgumienn <mgumienn@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 19:06:08 by mgumienn          #+#    #+#             */
/*   Updated: 2025/12/20 12:57:11 by mgumienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

typedef struct s_box
{
	int		nbr;
	long	die;
	long	eat;
	long	sleep;
	int		eat_count;
}	t_box;

int	ft_error(char *s, int status);
int	validate(int argc, char **argv, t_box *box);
