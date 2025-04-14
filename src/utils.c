/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:23:08 by mg                #+#    #+#             */
/*   Updated: 2025/04/14 10:17:01 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void    exit_error(const char *error)
{
    printf(RED"%s \n",RST, error);
    exit(EXIT_FAILURE);
}

inline bool is_digit(char c)
{
    return (c >= '0' && c <= 9);
}

void    *safe_malloc(size_t bytes)
{
    void    *retrn;
    retrn = malloc(bytes);
    if (!retrn)
        exit_error(RED"Error with allocation memory.."RST);
    return (retrn);
}