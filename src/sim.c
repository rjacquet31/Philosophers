/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:13:51 by rafael            #+#    #+#             */
/*   Updated: 2025/03/07 14:13:51 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	start_simulation(t_table *table)
{
	size_t	i;

	table->start_time = get_ms();
	i = -1;
	while (++i < table->nb_philo)
	{
		if (pthread_create(&table->philos[i]->thread, NULL,
				&run_simulation, table->philos[i]) != 0)
			return (ERROR);
	}
	if (table->nb_philo > 1)
	{
		if (pthread_create(&table->monitoring, NULL,
				&monitor_philosophers, table) != 0)
			return (ERROR);
	}
	return (SUCCESS);
}

int	stop_simulation(t_table *table)
{
	size_t	i;

	i = -1;
	while (++i < table->nb_philo)
		pthread_join(table->philos[i]->thread, NULL);
	if (table->nb_philo > 1)
		pthread_join(table->monitoring, NULL);
	return (SUCCESS);
}

void	*run_simulation(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->m_meal);
	philo->last_meal = philo->table->start_time;
	pthread_mutex_unlock(&philo->m_meal);
	set_simulation_status(philo->table, TRUE);
	if (philo->table->nb_philo == 1)
		return (dead(philo));
	else if (philo->id % 2)
		start_thinking(philo);
	while (is_simulation_running(philo) == TRUE)
	{
		start_eating_then_sleeping(philo);
		start_thinking(philo);
	}
	return (NULL);
}
