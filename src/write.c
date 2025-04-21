/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:24:28 by mg                #+#    #+#             */
/*   Updated: 2025/04/21 15:56:08 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void    write_status(t_philo_status status, t_philo *philo)
{
    long    elapsed;
   
    elapsed = get_time(MILLISECOND) - philo->table->start;
    if (philo->full)
        return;
    
    safe_mutex_handle(&philo->table->write_mtx, LOCK);
   
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

    safe_mutex_handle(&philo->table->write_mtx, UNLOCK);
}