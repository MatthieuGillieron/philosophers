/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:20:49 by mg                #+#    #+#             */
/*   Updated: 2025/04/15 13:52:05 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"






void    *dinner_simu(void *data)
{
    t_philo *philo;
    
    philo = (t_philo *)data;

    wait_thread(philo->table);
}




/*
    - si pas de repas -> return 0
    - si seulement 1 philo -> ?
    - cree tout les thread, tout les philos
    - cree un thread qui check si mort 
    - syncro le debut -> tout les philo commence en mm temps
    - join
    
*/

void    dinner_start(t_table *table)
{
    int i;

    i = -1;
    if (0 == table->limit_meals)
        return;
    else if (1 == table->philo_nbr)
        ;//voir
    else
    {

        while(++i < table->philo_nbr)
            safe_thread_handle(table->philos[i].thread_id, dinner_simu,
                &table->philos[i], CREATE);
    }
    
}