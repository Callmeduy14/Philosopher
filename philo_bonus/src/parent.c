/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 09:01:01 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/30 10:45:48 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	kill_all(t_shared *sh)
{
	int	i;

	i = 0;
	while (i < sh->a.n)
	{
		if (sh->pids[i] > 0)
			kill(sh->pids[i], SIGTERM);
		i++;
	}
}

static int	spawn_children(t_shared *sh)
{
	int		i;
	pid_t	pid;

	sh->start_ms = now_ms();
	i = 0;
	while (i < sh->a.n)
	{
		pid = fork();
		if (pid < 0)
			return (-1);
		if (pid == 0)
			run_child(sh, i + 1);
		sh->pids[i++] = pid;
	}
	return (0);
}

static void	wait_all_full_then_kill(t_shared *sh)
{
	int	i;

	i = 0;
	while (i < sh->a.n)
	{
		sem_wait(sh->full);
		i++;
	}
	kill_all(sh);
	while (waitpid(-1, NULL, 0) > 0)
		;
}

static void	wait_one_death_then_kill(t_shared *sh)
{
	int	status;

	waitpid(-1, &status, 0);
	kill_all(sh);
	while (waitpid(-1, NULL, 0) > 0)
		;
}

void	run_parent(t_shared *sh)
{
	if (spawn_children(sh) < 0)
	{
		kill_all(sh);
		while (waitpid(-1, NULL, 0) > 0)
			;
		return ;
	}
	if (sh->a.must_eat > 0)
		wait_all_full_then_kill(sh);
	else
		wait_one_death_then_kill(sh);
}
