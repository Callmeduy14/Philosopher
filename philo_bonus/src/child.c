/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 09:00:43 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/30 10:42:56 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	print_state(t_ph *p, const char *msg)
{
	long	t;

	sem_wait(p->sh->print);
	t = now_ms() - p->sh->start_ms;
	printf("%ld %d %s\n", t, p->id, msg);
	fflush(stdout);
	sem_post(p->sh->print);
}

static void	*watchdog(void *arg)
{
	t_ph	*p;

	p = (t_ph *)arg;
	while (1)
	{
		if (now_ms() - p->last_meal > p->sh->a.t_die)
		{
			sem_wait(p->sh->print);
			printf("%ld %d died\n", now_ms() - p->sh->start_ms, p->id);
			fflush(stdout);
			sem_post(p->sh->print);
			exit(1);
		}
		usleep(1000);
	}
	return (NULL);
}

static void	eat_once(t_ph *p)
{
	sem_wait(p->sh->forks);
	print_state(p, "has taken a fork");
	sem_wait(p->sh->forks);
	print_state(p, "has taken a fork");
	p->last_meal = now_ms();
	print_state(p, "is eating");
	msleep_loop(p->sh->a.t_eat);
	sem_post(p->sh->forks);
	sem_post(p->sh->forks);
	p->meals += 1;
	if (p->sh->a.must_eat > 0 && p->meals == p->sh->a.must_eat)
		sem_post(p->sh->full);
	print_state(p, "is sleeping");
	msleep_loop(p->sh->a.t_sleep);
	print_state(p, "is thinking");
}

void	run_child(t_shared *sh, int id)
{
	pthread_t	th;
	t_ph		p;

	p.id = id;
	p.meals = 0;
	p.sh = sh;
	p.last_meal = now_ms();
	pthread_create(&th, NULL, &watchdog, &p);
	pthread_detach(th);
	if (p.id % 2 == 0)
		usleep(500);
	while (1)
		eat_once(&p);
}
