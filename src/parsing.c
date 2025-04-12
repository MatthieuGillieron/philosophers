/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:28:39 by mg                #+#    #+#             */
/*   Updated: 2025/04/12 23:10:39 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static const char   *valid_input(const char *str)
{
    int         len;
    int         i;
    const char  *nbr;

    len = 0;
    i = 0;
    while (str)
    {
        if (str[i] >= 9 && str[i] <= 13 || str[i] == 32)
            i++;
        if (str[i] == '+')
            i++;
        else if (str[i] == '-')
            exit_error(RED"Only positive value.."RST);
        if (!str[i] >= 0 && !str[i] <= 9)
            exit_error(RED"The input need to be a digit.."RST);
    }
}


static long ft_atol(const char *str)
{
    long    nbr;

    nbr = 0;
    str = valid_input(nbr);
}


void    parse_input(t_table *table, char **av)
{
    table->philo_nbr = ft_atol(av[1]);
}