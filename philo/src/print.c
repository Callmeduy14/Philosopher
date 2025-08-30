/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 08:59:38 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/30 10:33:12 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	stopped(t_shared *sh)
{
	int	s;

	pthread_mutex_lock(&sh->stop_mtx);
	s = sh->stop;
	pthread_mutex_unlock(&sh->stop_mtx);
	return (s);
}

void	set_stop(t_shared *sh)
{
	pthread_mutex_lock(&sh->stop_mtx);
	sh->stop = 1;
	pthread_mutex_unlock(&sh->stop_mtx);
}

void	safe_print(t_shared *sh, int id, const char *msg)
{
	long	t;

	pthread_mutex_lock(&sh->print_mtx);
	if (!stopped(sh))
	{
		t = now_ms() - sh->start_ms;
		printf("%ld %d %s\n", t, id, msg);
		fflush(stdout);
	}
	pthread_mutex_unlock(&sh->print_mtx);
}
