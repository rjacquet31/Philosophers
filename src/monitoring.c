/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:21:18 by rafael            #+#    #+#             */
/*   Updated: 2025/03/07 14:21:18 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*monitor_philosophers(void *ptr)
{
	t_table	*table;

	table = (t_table *)ptr;
	set_simulation_status(table, TRUE);
	while (1)
	{
		if (is_end_of_dinner(table) == TRUE)
			return (NULL);
		ft_msleep(5);
	}
}

int	is_simulation_running(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->table->m_simulation);
	result = philo->table->sim_running;
	pthread_mutex_unlock(&philo->table->m_simulation);
	return (result);
}

int	is_someone_dead(t_philo *philo)
{
	if ((get_ts(philo) - philo->last_meal) >= philo->table->time_to_die)
	{
		set_simulation_status(philo->table, FALSE);
		process_status(philo, get_ts(philo), DEAD);
		pthread_mutex_unlock(&philo->m_meal);
		return (TRUE);
	}
	return (FALSE);
}

void	set_simulation_status(t_table *table, int status)
{
	pthread_mutex_lock(&table->m_simulation);
	table->sim_running = status;
	pthread_mutex_unlock(&table->m_simulation);
}

int	is_end_of_dinner(t_table *table)
{
	size_t	i;
	int		everybody_is_full;

	everybody_is_full = TRUE;
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_lock(&table->philos[i]->m_meal);
		if (is_someone_dead(table->philos[i]))
			return (TRUE);
		if (table->min_nb_meal != -1)
			if (table->philos[i]->nb_meal < table->min_nb_meal)
				everybody_is_full = FALSE;
		pthread_mutex_unlock(&table->philos[i]->m_meal);
		i++;
	}
	if (table->min_nb_meal != -1 && everybody_is_full == TRUE)
	{
		set_simulation_status(table, FALSE);
		pthread_mutex_lock(&table->m_print);
		printf("Everyone as eaten %d times\n", table->min_nb_meal);
		pthread_mutex_unlock(&table->m_print);
		return (TRUE);
	}
	return (FALSE);
}
