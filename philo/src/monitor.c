/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 10:36:10 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/30 10:36:12 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_full(t_shared *sh)
{
	if (sh->a.must_eat > 0 && sh->full_count >= sh->a.n)
	{
		sh->stop = 1;
		return (1);
	}
	return (0);
}

static int	check_death(t_shared *sh, int i)
{
	long	t;

	t = now_ms() - sh->ph[i].last_meal;
	if (t > sh->a.t_die)
	{
		sh->stop = 1;
		pthread_mutex_unlock(&sh->stop_mtx);
		pthread_mutex_lock(&sh->print_mtx);
		printf("%ld %d died\n", now_ms() - sh->start_ms, sh->ph[i].id);
		fflush(stdout);
		pthread_mutex_unlock(&sh->print_mtx);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_shared	*sh;
	int			i;

	sh = (t_shared *)arg;
	while (!stopped(sh))
	{
		i = 0;
		while (i < sh->a.n && !stopped(sh))
		{
			pthread_mutex_lock(&sh->stop_mtx);
			if (check_full(sh) || check_death(sh, i))
				return (NULL);
			pthread_mutex_unlock(&sh->stop_mtx);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
