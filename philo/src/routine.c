/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 10:35:36 by yyudi             #+#    #+#             */
/*   Updated: 2025/09/07 13:50:01 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	reached_quota(t_philo *p)
{
	int	ok;

	ok = 0;
	if (p->sh->a.must_eat > 0)
	{
		pthread_mutex_lock(&p->sh->stop_mtx);
		if (p->meals >= p->sh->a.must_eat)
			ok = 1;
		pthread_mutex_unlock(&p->sh->stop_mtx);
	}
	return (ok);
}

static void	post_think_stagger(t_philo *p)
{
	if (p->id % 2)
		usleep(500);
}

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->id % 2 == 0)
		usleep(1000);
	while (!stopped(p->sh))
	{
		if (reached_quota(p))
			break ;
		eat_cycle(p);
		if (reached_quota(p) || stopped(p->sh))
			break ;
		safe_print(p->sh, p->id, "is sleeping");
		msleep_loop(p->sh->a.t_sleep, p->sh);
		if (stopped(p->sh))
			break ;
		safe_print(p->sh, p->id, "is thinking");
		post_think_stagger(p);
	}
	return (NULL);
}
