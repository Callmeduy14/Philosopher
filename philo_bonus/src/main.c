/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 09:00:53 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/30 10:43:12 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	usage(void)
{
	printf("Usage: philo_bonus n t_die t_eat t_sleep [must_eat]\n");
}

int	main(int ac, char **av)
{
	t_args		a;
	t_shared	sh;

	if (ac != 5 && ac != 6)
		return (usage(), 1);
	if (parse_args(&a, ac, av) != 0)
		return (fprintf(stderr, "Invalid arguments\n"), 1);
	if (init_shared(&sh, &a) != 0)
		return (fprintf(stderr, "Init failed\n"), 1);
	run_parent(&sh);
	destroy_shared(&sh);
	return (0);
}
