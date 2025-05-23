/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:20:49 by mg                #+#    #+#             */
/*   Updated: 2025/04/24 16:57:51 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

/**
 * @brief Gère l'état de réflexion d'un philosophe
 * calcul le temps de reflexion pour eviter les deadlock (pas que tt les
 * philo veulent prendre une fourchette en mm temps!)
 * pour un nbr impair de philo on utilise * 0.42 pour desynchroniser
 */

void	thinking(t_philo *philo, bool pre_sim)
{
	long	time_eat;
	long	time_sleep;
	long	time_think;

	if (!pre_sim)
		write_status(THINKING, philo);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	time_eat = philo->table->time_to_eat;
	time_sleep = philo->table->time_to_sleep;
	time_think = time_eat * 2 - time_sleep;
	if (time_think < 0)
		time_think = 0;
	better_usleep(time_think * 0.42, philo->table);
}

void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_thread(philo->table);
	set_long(&philo->philo_mtx, &philo->last_meal, get_time(MILLISECOND));
	increase_long(&philo->table->table_mtx, &philo->table->thread_running_nbr);
	write_status(TAKE_FIRST_WORK, philo);
	while (!sim_finish(philo->table))
		usleep(200);
	return (NULL);
}

/**
 * @brief Simule l'action de manger pour un philosophe
 * prise fourchette / mange / check si philo > balou :)
 * libere fourchette
 */

static void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_WORK, philo);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mtx, &philo->last_meal, get_time(MILLISECOND));
	philo->meals_counter++;
	write_status(EATING, philo);
	better_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->limit_meals > 0
		&& philo->meals_counter == philo->table->limit_meals)
		set_bool(&philo->philo_mtx, &philo->full, true);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

/**
 * thread de philosophe 
 * cycle complet d'un philo
 * attendre tout les thread ok pour que tout demarre en mm temps
 * pas qu un philo manger en avance ... par rapport a un autres..

 */

void	*dinner_simu(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_thread(philo->table);
	set_long(&philo->philo_mtx, &philo->last_meal, get_time(MILLISECOND));
	increase_long(&philo->table->table_mtx,
		&philo->table->thread_running_nbr);
	desynchro_philo(philo);
	while (!sim_finish(philo->table))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(SLEEPING, philo);
		better_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo, false);
	}
	return (NULL);
}

/*
 * 
 * initialise et lance tous les threads nécessaires à la simulation:
 * - Un thread par philosophe (ou thread spécial si 1 seul philosophe)
 * - Un thread moniteur qui vérifie si un philosophe meurt de faim
 * 
 * attend ensuite que tous les threads de philos se terminent avant
 * de terminer la sim. et de rejoindre le thread moniteur
 */

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (0 == table->limit_meals)
		return ;
	else if (1 == table->philo_nbr)
		safe_thread_handle(&table->philos[0].thread_id,
			lone_philo, &table->philos[0], CREATE);
	else
	{
		while (++i < table->philo_nbr)
			safe_thread_handle(&table->philos[i].thread_id, dinner_simu,
				&table->philos[i], CREATE);
	}
	safe_thread_handle(&table->monitor, monitor_dinner, table, CREATE);
	table->start = get_time(MILLISECOND);
	set_bool(&table->table_mtx, &table->all_thread, true);
	i = -1;
	while (++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mtx, &table->end, true);
	safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
}
