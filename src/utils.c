/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:23:08 by mg                #+#    #+#             */
/*   Updated: 2025/04/14 14:01:25 by mg               ###   ########.fr       */
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


/*
    EINVAL  :	Invalid argument        ->	Tu as passé un argument invalide à une fonction. Ex: mutex pas init.
    EDEADLK :	Deadlock detected       ->	Tu es en train de créer un deadlock (genre tu relock un mutex que tu tiens déjà).
    EPERM   :	Operation not permitted ->	T’essaies de faire une opération pour laquelle tu n’as pas le droit (ex: unlock un mutex que tu n’as pas locké).
    ENOMEM  :	Not enough memory       ->	Plus assez de mémoire pour faire ce que tu veux (ex: créer un mutex).
    EBUSY   :	Resource busy           ->	Ressource occupée. Par exemple : mutex encore locké, donc tu peux pas le détruire.
*/

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
        handle_mtx_error(pthread_mutex_lock(mutex), opcode);
    else if (UNLOCK == opcode)
        handle_mtx_error(pthread_mutex_unlock(mutex), opcode);
    else if (INIT == opcode)
        handle_mtx_error(pthread_mutex_init(mutex, NULL), opcode);
    else if (DESTROY == opcode)
        handle_mtx_error(pthread_mutex_destroy(mutex), opcode);
    else
        exit_error(RED"Wrong opcode for mutex.."RST);
}
