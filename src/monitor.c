/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:54:18 by mg                #+#    #+#             */
/*   Updated: 2025/04/19 22:02:42 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"




static bool philo_died(t_philo *philo)
{
    long    elapsed;
    long    time_2_die;

    if (get_bool(&philo->philo_mtx, &philo->full))
        return (false);

    elapsed = get_time(MILLISECOND) - get_long(&philo->philo_mtx, &philo->last_meal);
    time_2_die = philo->table->time_to_die / 1e3;

    if (elapsed > time_2_die)
        return (true);
    return (false);
}





void    *monitor_dinner(void *data)
{
    int     i;
    t_table *table;

    table = (t_table *)data;

    while (!all_thread_run(&table->table_mtx, &table->thread_running_nbr, table->philo_nbr))
        ;
    while (!sim_finish(table))
    {
        i = -1;
        while(++i < table->philo_nbr && !sim_finish(table))
        {
            if (philo_died(table->philos + i))
            {
                set_bool(&table->table_mtx, &table->end, true);
                write_status(DIED, table->philos + i, DEBUG_MODE);
            }
        }
    }
    return (NULL);
}