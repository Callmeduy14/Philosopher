/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 08:59:50 by yyudi             #+#    #+#             */
/*   Updated: 2025/09/07 13:45:34 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sim_start(t_shared *sh)
{
	int	i;

	sh->start_ms = now_ms();
	pthread_mutex_lock(&sh->stop_mtx);
	i = 0;
	while (i < sh->a.n)
	{
		sh->ph[i].last_meal = sh->start_ms;
		i++;
	}
	pthread_mutex_unlock(&sh->stop_mtx);
	i = 0;
	while (i < sh->a.n)
	{
		if (pthread_create(&sh->ph[i].th, NULL, \
				&philo_routine, &sh->ph[i]) != 0)
			set_stop(sh);
		i++;
	}
	if (pthread_create(&sh->monitor, NULL, &monitor_routine, sh) != 0)
		set_stop(sh);
}

void	sim_join_and_cleanup(t_shared *sh)
{
	int	i;

	pthread_join(sh->monitor, NULL);
	i = 0;
	while (i < sh->a.n)
	{
		pthread_join(sh->ph[i].th, NULL);
		i++;
	}
	destroy_shared(sh);
}
