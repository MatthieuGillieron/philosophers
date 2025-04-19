/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:56:13 by mg                #+#    #+#             */
/*   Updated: 2025/04/19 22:09:22 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void    wait_thread(t_table *table)
{
    while (!get_bool(&table->table_mtx, &table->all_thread))
        ;
}

bool    all_thread_run(t_mtx *mutex, long *threads, long philo_nbr)
{
    bool    ret;

    ret = false;
    safe_mutex_handle(mutex, LOCK);
    if (*threads == philo_nbr)
        ret = true;
    safe_mutex_handle(mutex, UNLOCK);
    return (ret);
}


void increase_long(t_mtx *mutex, long *value)
{
    safe_mutex_handle(mutex, LOCK);
    (*value)++;
    safe_mutex_handle(mutex, UNLOCK);
}