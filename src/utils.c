/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:23:08 by mg                #+#    #+#             */
/*   Updated: 2025/04/14 13:38:31 by mg               ###   ########.fr       */
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

static void handle_mtx_error(int status, t_opcode opcode)
{
    if (0 == status)
        return;
        if (EINVAL == status && (LOCK == opcode || UNLOCK == opcode
            || DESTROY == opcode))
            exit_error(RED"Value specified by mutex is broken.."RST);
        else if (EINVAL == status && INIT == opcode)
            exit_error(RED"Value specified by attr not valid.."RST);
        else if (EDEADLK == status)
            exit_error(RED"Deadlock would occur if the thread wainting for mutex.."RST);
        else if (EPERM == status)
            exit_error(RED"Current thread does not hold a lock on mutex.."RST);
        else if (ENOMEM == status)
            exit_error(RED"Process cant allocate memory to create another mutex.."RST);
        else if (EBUSY == status)
            exit_error(RED"Mutex locked.."RST);
}


void    safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
    if (LOCK == opcode)
        pthread_mutex_lock(mutex);
    else if (UNLOCK == opcode)
        pthread_mutex_unlock(mutex);
    else if (INIT == opcode)
        pthread_mutex_init(mutex, NULL);
    else if (DESTROY == opcode)
        pthread_mutex_destroy(mutex);
    else
        exit_error(RED"Wrong opcode for mutex.."RST);
}
