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

void	*run_simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (is_simulation_running(philo))
	{
		if (philo->status == DEAD)
		{
			pthread_mutex_lock(&philo->table->m_simulation);
			philo->table->sim_running = FALSE;
			pthread_mutex_unlock(&philo->table->m_simulation);
			break ;
		}
		start_thinking(philo);
		start_eating_then_sleeping(philo);
	}
	return (NULL);
}

int	start_simulation(t_table *table)
{
	size_t	i;

	table->start_time = get_ms();
	if (pthread_create(&table->monitoring, NULL,
			monitor_philosophers, table) != 0)
		return (process_exit(ERROR, table,
				"Error: pthread_create (monitor) failed\n"));
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_create(&table->philos[i]->thread, NULL,
				run_simulation, table->philos[i]) != 0)
			return (process_exit(ERROR, table,
					"Error: pthread_create (philo) failed\n"));
		i++;
	}
	return (SUCCESS);
}

int	stop_simulation(t_table *table)
{
	size_t	i;

	pthread_join(table->monitoring, NULL);
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_join(table->philos[i]->thread, NULL);
		i++;
	}
	return (SUCCESS);
}
