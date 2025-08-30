/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 09:00:05 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/30 10:34:19 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_shared *sh)
{
	int	i;

	i = 0;
	while (i < sh->a.n)
	{
		sh->ph[i].id = i + 1;
		sh->ph[i].left = &sh->forks[i];
		sh->ph[i].right = &sh->forks[(i + 1) % sh->a.n];
		if (sh->ph[i].id % 2 == 0)
		{
			sh->ph[i].left = &sh->forks[(i + 1) % sh->a.n];
			sh->ph[i].right = &sh->forks[i];
		}
		sh->ph[i].meals = 0;
		sh->ph[i].sh = sh;
		i++;
	}
}

int	init_shared(t_shared *sh, t_args *a)
{
	int	i;

	memset(sh, 0, sizeof(*sh));
	sh->a = *a;
	if (pthread_mutex_init(&sh->stop_mtx, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&sh->print_mtx, NULL) != 0)
		return (-1);
	sh->forks = (t_fork *)malloc(sizeof(t_fork) * a->n);
	sh->ph = (t_philo *)malloc(sizeof(t_philo) * a->n);
	if (!sh->forks || !sh->ph)
		return (-1);
	i = 0;
	while (i < a->n)
	{
		if (pthread_mutex_init(&sh->forks[i].mtx, NULL) != 0)
			return (-1);
		i++;
	}
	assign_forks(sh);
	return (0);
}

void	destroy_shared(t_shared *sh)
{
	int	i;

	i = 0;
	while (i < sh->a.n)
	{
		pthread_mutex_destroy(&sh->forks[i].mtx);
		i++;
	}
	pthread_mutex_destroy(&sh->print_mtx);
	pthread_mutex_destroy(&sh->stop_mtx);
	free(sh->forks);
	free(sh->ph);
}
