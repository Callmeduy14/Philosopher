/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 09:01:06 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/30 10:43:55 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

long	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

void	msleep_loop(long ms)
{
	long	end;

	end = now_ms() + ms;
	while (now_ms() < end)
		usleep(100);
}
