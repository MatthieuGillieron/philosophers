/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:28:39 by mg                #+#    #+#             */
/*   Updated: 2025/04/14 09:54:08 by mg               ###   ########.fr       */
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
    while (is_digit(*str))
        nbr = (nbr * 10) + (*str++ - '0');
    if (nbr > INT_MAX)
        exit_error(RED"Value is too big.."RST);
    return (nbr);
}


/*
    input : ./philo 5 800 200 200 [5]
                    ms   ms  ms
                    
       seconde      1s
       miliseconde  1/1000s
       microseconde 1/1,000,000s

        1e3 -> 1000 "notation scientifique pour dire 1 est 3 zero.." 
        6e4-> 60000 -> Micro -> 60 -> ms 
                          
        time_to_... sont donner en MS et usleep est en microseconde
        donc convertir
        usleep(800)-> 0.8ms
*/

void    parse_input(t_table *table, char **av)
{
    table->philo_nbr = ft_atol(av[1]);
    table->time_to_die = ft_atol(av[2]) * 1e3;
    table->time_to_eat = ft_atol(av[3]) * 1e3;
    table->time_to_sleep = ft_atol(av[4]) * 1e3;
    if (table->time_to_die < 6e4 || table->time_to_eat < 6e4
        || table->time_to_sleep < 6e4)
        exit_error(RED"Need timestamps >= 60MS..."RST);
    if (av[5])
        table->limit_meals = ft_atol(av[5]);
    else
        table->limit_meals = -1;    
}