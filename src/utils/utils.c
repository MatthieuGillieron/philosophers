/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:23:08 by mg                #+#    #+#             */
/*   Updated: 2025/04/28 15:22:20 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	exit_error(const char *error)
{
	printf(RED"%s \n"RST, error);
	return (EXIT_FAILURE);
}

bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

void	*safe_malloc(size_t bytes)
{
	void	*retrn;

	retrn = malloc(bytes);
	if (!retrn)
	{
		exit_error(RED"Error with allocation memory.."RST);
		return (NULL);
	}
	return (retrn);
}

void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		safe_mutex_handle(&philo->philo_mtx, DESTROY);
	}
	safe_mutex_handle(&table->write_mtx, DESTROY);
	safe_mutex_handle(&table->table_mtx, DESTROY);
	free(table->forks);
	free(table->philos);
}
