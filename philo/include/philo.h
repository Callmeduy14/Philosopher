/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 08:59:22 by yyudi             #+#    #+#             */
/*   Updated: 2025/09/03 12:25:37 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_args
{
	int		n;
	long	t_die;
	long	t_eat;
	long	t_sleep;
	int		must_eat;
}	t_args;

typedef struct s_fork
{
	pthread_mutex_t	mtx;
}	t_fork;

typedef struct s_shared	t_shared;

typedef struct s_philo
{
	int			id;
	pthread_t	th;
	t_fork		*left;
	t_fork		*right;
	long		last_meal;
	int			meals;
	t_shared	*sh;
}		t_philo;

struct				s_shared
{
	t_args			a;
	long			start_ms;
	int				stop;
	pthread_mutex_t	stop_mtx;
	pthread_mutex_t	print_mtx;
	t_fork			*forks;
	t_philo			*ph;
	pthread_t		monitor;
	int				full_count;
};

int		parse_args(t_args *a, int ac, char **av);
long	now_ms(void);
void	eat_cycle(t_philo *p);
void	msleep_loop(long ms, t_shared *sh);
void	*monitor_routine(void *arg);
void	*philo_routine(void *arg);
void	sim_start(t_shared *sh);
void	sim_join_and_cleanup(t_shared *sh);
void	safe_print(t_shared *sh, int id, const char *msg);
int		stopped(t_shared *sh);
void	set_stop(t_shared *sh);
int		init_shared(t_shared *sh, t_args *a);
void	destroy_shared(t_shared *sh);

#endif
