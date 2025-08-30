/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 08:59:11 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/30 10:11:33 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	usage(void)
{
	printf("Usage: philo n t_die t_eat t_sleep [must_eat]\n");
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
	sim_start(&sh);
	sim_join_and_cleanup(&sh);
	return (0);
}
