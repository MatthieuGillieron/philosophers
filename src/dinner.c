/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:20:49 by mg                #+#    #+#             */
/*   Updated: 2025/04/17 11:49:54 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*
    1: Prendre prend fourchette est lock
    2: eat, update dernier repas, update le counter | philo is full ?
    3: reposer les fourchettes
*/


static void eat(t_philo *philo)
{
    safe_mutex_handle(&philo->first_fork->fork, LOCK);
    write_status(TAKE_FIRST_WORK, philo, DEBUG_MODE);
    safe_mutex_handle(&philo->second_fork->fork, LOCK);
    write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);

    set_long(&philo->philo_mtx, &philo->last_meal, get_time(MILLISECOND));
    philo->meals_counter++;
    write_status(EATING, philo, DEBUG_MODE);
    better_usleep(philo->table->time_to_eat, philo->table);
    if (philo->table->limit_meals > 0
        && philo->meals_counter == philo->table->limit_meals)
        set_bool(&philo->philo_mtx, &philo->full, true);

        safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
        safe_mutex_handle(&philo->second_fork->fork, UNLOCK);

}




void    *dinner_simu(void *data)
{
    t_philo *philo;
    
    philo = (t_philo *)data;

    wait_thread(philo->table);

    while (!sim_finish(philo->table))
    {
        if (philo->full)
            break;
        
        eat(philo);

        // sleep
        write_status(SLEEPING, philo, DEBUG_MODE);
        better_usleep(philo->table->time_to_sleep, philo->table);

        // think
        

    }
    return (NULL);
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
    table->start = get_time(MILLISECOND);

    set_bool(&table->table_mtx, &table->all_thread, true);

    //wait for all
    i = -1;
    while (++i < table->philo_nbr)
        safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
    
}