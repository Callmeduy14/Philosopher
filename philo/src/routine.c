/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 10:35:36 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/30 10:40:18 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_fork(t_shared *sh, t_fork *f, int id)
{
	pthread_mutex_lock(&f->mtx);
	safe_print(sh, id, "has taken a fork");
}

static void	put_fork(t_fork *f)
{
	pthread_mutex_unlock(&f->mtx);
}

static void	eat_cycle(t_philo *p)
{
	take_fork(p->sh, p->left, p->id);
	if (p->left == p->right)
	{
		msleep_loop(p->sh->a.t_die + 1, p->sh);
		return ;
	}
	take_fork(p->sh, p->right, p->id);
	pthread_mutex_lock(&p->sh->stop_mtx);
	p->last_meal = now_ms();
	pthread_mutex_unlock(&p->sh->stop_mtx);
	safe_print(p->sh, p->id, "is eating");
	msleep_loop(p->sh->a.t_eat, p->sh);
	pthread_mutex_lock(&p->sh->stop_mtx);
	p->meals += 1;
	if (p->sh->a.must_eat > 0 && p->meals == p->sh->a.must_eat)
		p->sh->full_count += 1;
	pthread_mutex_unlock(&p->sh->stop_mtx);
	put_fork(p->right);
	put_fork(p->left);
}

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->id % 2 == 0)
		usleep(500);
	while (!stopped(p->sh))
	{
		eat_cycle(p);
		safe_print(p->sh, p->id, "is sleeping");
		msleep_loop(p->sh->a.t_sleep, p->sh);
		safe_print(p->sh, p->id, "is thinking");
	}
	return (NULL);
}
