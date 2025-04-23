/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:23:12 by mg                #+#    #+#             */
/*   Updated: 2025/04/23 21:04:05 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

/*
        input : ./philo 5 800 200 200 [5]
    nbr_philo, time_die time_eat time_sleep [must_eat]
*/

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		parse_input(&table, av);
		data_init(&table);
		dinner_start(&table);
		clean(&table);
	}
	else
	{
		exit_error(RED"Bad input..\n"RST
			GREEN"tape: ./philo 5 800 200 200 [5]"RST);
	}
}
