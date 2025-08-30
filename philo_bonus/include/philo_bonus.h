/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 19:00:00 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/30 10:44:28 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>

typedef struct s_args
{
	int		n;
	long	t_die;
	long	t_eat;
	long	t_sleep;
	int		must_eat;
}		t_args;

typedef struct s_shared
{
	t_args	a;
	long	start_ms;
	sem_t	*forks;
	sem_t	*print;
	sem_t	*full;
	int		*pids;
}		t_shared;

typedef struct s_ph
{
	int			id;
	long		last_meal;
	int			meals;
	t_shared	*sh;
}		t_ph;

int		parse_args(t_args *a, int ac, char **av);
long	now_ms(void);
void	msleep_loop(long ms);
int		init_shared(t_shared *sh, t_args *a);
void	destroy_shared(t_shared *sh);
void	run_parent(t_shared *sh);
void	run_child(t_shared *sh, int id);

#endif
