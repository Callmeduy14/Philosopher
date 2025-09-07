/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eatcycle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:11:27 by yyudi             #+#    #+#             */
/*   Updated: 2025/09/07 13:50:18 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_fork(t_shared *sh, t_fork *f, int id)
{
	pthread_mutex_lock(&f->mtx);
	safe_print(sh, id, "has taken a fork");
}

static void	pick_order(t_philo *p, t_fork **first, t_fork **second)
{
	int	li;
	int	ri;

	li = (int)(p->left - p->sh->forks);
	ri = (int)(p->right - p->sh->forks);
	*first = p->left;
	*second = p->right;
	if (li >= ri)
	{
		*first = p->right;
		*second = p->left;
	}
}

static void	begin_eat(t_philo *p)
{
	pthread_mutex_lock(&p->sh->stop_mtx);
	p->last_meal = now_ms();
	pthread_mutex_unlock(&p->sh->stop_mtx);
	safe_print(p->sh, p->id, "is eating");
	msleep_loop(p->sh->a.t_eat, p->sh);
}

void	eat_cycle(t_philo *p)
{
	t_fork	*first;
	t_fork	*second;

	pick_order(p, &first, &second);
	take_fork(p->sh, first, p->id);
	if (p->left == p->right)
	{
		msleep_loop(p->sh->a.t_die + 1, p->sh);
		pthread_mutex_unlock(&first->mtx);
		return ;
	}
	take_fork(p->sh, second, p->id);
	begin_eat(p);
	pthread_mutex_lock(&p->sh->stop_mtx);
	p->meals += 1;
	if (p->sh->a.must_eat > 0 && p->meals == p->sh->a.must_eat)
	{
		p->sh->full_count += 1;
		if (p->sh->full_count >= p->sh->a.n)
			p->sh->stop = 1;
	}
	pthread_mutex_unlock(&p->sh->stop_mtx);
	pthread_mutex_unlock(&second->mtx);
	pthread_mutex_unlock(&first->mtx);
}
