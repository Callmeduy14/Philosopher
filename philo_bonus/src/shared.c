/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 09:01:14 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/30 09:01:16 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	open_sem(sem_t **s, const char *name, int val)
{
	sem_unlink(name);
	*s = sem_open(name, O_CREAT | O_EXCL, 0644, val);
	if (*s == SEM_FAILED)
		return (-1);
	return (0);
}

int	init_shared(t_shared *sh, t_args *a)
{
	memset(sh, 0, sizeof(*sh));
	sh->a = *a;
	if (open_sem(&sh->forks, "/philo_forks", a->n) != 0)
		return (-1);
	if (open_sem(&sh->print, "/philo_print", 1) != 0)
		return (-1);
	if (open_sem(&sh->full, "/philo_full", 0) != 0)
		return (-1);
	sh->pids = (int *)malloc(sizeof(int) * a->n);
	if (!sh->pids)
		return (-1);
	return (0);
}

void	destroy_shared(t_shared *sh)
{
	if (sh->forks)
		sem_close(sh->forks);
	if (sh->print)
		sem_close(sh->print);
	if (sh->full)
		sem_close(sh->full);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_print");
	sem_unlink("/philo_full");
	free(sh->pids);
}
