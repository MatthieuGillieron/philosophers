/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:28:39 by mg                #+#    #+#             */
/*   Updated: 2025/04/12 23:58:20 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static const char   *valid_input(const char *str)
{
    int         len;
    const char  *nbr;

    len = 0;
    if (!str || !*str)
        exit_error(RED"Empty input"RST);

    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;

        if (*str == '+')
            str++;
        else if (*str == '-')
            exit_error(RED"Only positive value.."RST);

        if (!is_digit(*str))
            exit_error(RED"The input need to be a digit.."RST);

        nbr = str;
        while (is_digit(*str))
        {
            len++;
            str++;
        }
        if (len > 10)
            exit_error(RED"Value is too big.."RST);
        return nbr;
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