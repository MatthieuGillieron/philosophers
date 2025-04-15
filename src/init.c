/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:03:45 by mg                #+#    #+#             */
/*   Updated: 2025/04/15 13:05:37 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"



/*

    Philosophe	    philo_pos	  Right Fork	            Left Fork
        P0	            0	    forks[0] (F0)	    forks[(0+1)%5] = forks[1] (F1)
        P1	            1	    forks[1] (F1)	    forks[(1+1)%5] = forks[2] (F2)
        P2	            2	    forks[2] (F2)	    forks[(2+1)%5] = forks[3] (F3)
        P3	            3	    forks[3] (F3)	    forks[(3+1)%5] = forks[4] (F4)
        P4	            4	    forks[4] (F4)	    forks[(4+1)%5] = forks[0] (F0) ✅ cercle fermé

*/
static void assign_fork(t_philo *philo, t_fork *forks, int philo_pos)
{
    int philo_nbr;
    
    philo_nbr = philo->table->philo_nbr;

    philo->rigth_fork = &forks[philo_pos];
    philo->left_fork = &forks[(philo_pos + 1) % philo_nbr];
}

static  philo_init(t_table *table)
{
    int     i;
    t_philo *philo;

    i = -1;
    while (++i < table->philo_nbr)
    {
        philo = table->philos + i;
        philo->id = i + 1;
        philo->full = false;
        philo->meals_counter = 0;
        philo->table = table;
    }
}




void    data_init(t_table *table)
{
    int i;

    i = -1;
    table->end = false;
    table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
    table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
    while(++i < table->philo_nbr)
    {
        safe_mutex_handle(&table->forks[i].fork, INIT);
        table->forks[i].id_fork = i; // pour debug, savoir quel philo a quelle fourchetes
    }
}