/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:24:28 by mg                #+#    #+#             */
/*   Updated: 2025/04/16 14:24:51 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"




static void write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
    if (TAKE_FIRST_WORK == status && !sim_finish(philo->table))
        printf(WHITE"%6ld"RST" %d take the 1 fork 🍴"
            "\t\tn˚"BLUE"[ 🍴 %d 🍴]\n"RST, elapsed, philo->id,
            philo->first_fork->id_fork);

    else if (TAKE_SECOND_FORK == status && !sim_finish(philo->table))
        printf(WHITE"%6ld"RST" %d take the 2 fork 🍴"
            "\t\tn˚"BLUE"[ 🍴 %d 🍴]\n"RST, elapsed, philo->id,
            philo->first_fork->id_fork);

    else if (EATING == status && !sim_finish(philo->table))
       printf(WHITE"%6ld"CYAN" %d is eating 🍝"
        "\t\t\t"YELLOW"[🍝 %ld 🍝]\n"RST, elapsed, philo->id, philo->meals_counter);

    
    else if (SLEEPING == status && !sim_finish(philo->table))
        printf(WHITE"%6ld"RST" %d is sleeping 💤\n", elapsed, philo->id);

    else if (THINKING == status && !sim_finish(philo->table))
        printf(WHITE"%6ld"RST" %d is thinking 💭\n", elapsed, philo->id);

    else if (DIED == status)
        printf(RED"\t\t %6ld %d is dead 💀\n"RST, elapsed, philo->id);
       
}




void    write_status(t_philo_status status, t_philo *philo, bool debug)
{
    long    elapsed;

    elapsed = get_time(MILLISECOND);// - start
    if (philo->full)
        return;

    safe_mutex_handle(&philo->table->write_mtx, LOCK);
    if(debug)
        write_status_debug(status, philo, elapsed);
    else
    {   
        if ((TAKE_FIRST_WORK == status || TAKE_SECOND_FORK == status)
        && !sim_finish(philo->table))
        printf(WHITE"%-6ld"RST"%d taken a fork\n", elapsed, philo->id);
        else if (EATING == status && !sim_finish(philo->table))
            printf(WHITE"%-6ld"CYAN"%d is eating\n"RST, elapsed, philo->id);
        
        else if (SLEEPING == status && !sim_finish(philo->table))
            printf(WHITE"%-6ld"RST"%d is sleeping\n", elapsed, philo->id);

        else if (THINKING == status && !sim_finish(philo->table))
            printf(WHITE"%-6ld"RST"%d is thinkings\n", elapsed, philo->id);

        else if (DIED == status)
            printf(RED"%-6ld %d is died\n"RST, elapsed, philo->id);
    }


       safe_mutex_handle(&philo->table->write_mtx, UNLOCK);
}