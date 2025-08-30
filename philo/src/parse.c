/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 08:59:30 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/30 10:30:34 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	ato_pos(const char *s)
{
	long	n;
	int		i;

	n = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		n = n * 10 + (s[i] - '0');
		if (n > 2147483647)
			return (-1);
		i++;
	}
	return (n);
}

int	parse_args(t_args *a, int ac, char **av)
{
	a->n = (int)ato_pos(av[1]);
	a->t_die = ato_pos(av[2]);
	a->t_eat = ato_pos(av[3]);
	a->t_sleep = ato_pos(av[4]);
	a->must_eat = -1;
	if (ac == 6)
		a->must_eat = (int)ato_pos(av[5]);
	if (a->n < 1 || a->n > 200 || a->t_die < 60
		|| a->t_eat < 60 || a->t_sleep < 60)
		return (-1);
	if (ac == 6 && a->must_eat <= 0)
		return (-1);
	return (0);
}
