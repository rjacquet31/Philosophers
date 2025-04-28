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

void	*monitor_philosophers(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	set_simulation_status(table, TRUE);
	while (is_simulation_running(table->philos[0]))
	{
		if (is_end_of_dinner(table))
			break ;
		ft_msleep(5);
	}
	return (NULL);
}

int	is_simulation_running(t_philo *philo)
{
	int	active;

	active = FALSE;
	pthread_mutex_lock(&philo->table->m_simulation);
	if (philo->table->sim_running == TRUE)
		active = TRUE;
	pthread_mutex_unlock(&philo->table->m_simulation);
	return (active);
}

int	is_someone_dead(t_philo *philo)
{
	long	current_time;
	long	time_since_last_meal;

	current_time = get_ts(philo);
	time_since_last_meal = current_time - philo->last_meal;
	if (time_since_last_meal >= philo->table->time_to_die)
	{
		set_simulation_status(philo->table, FALSE);
		process_status(philo, current_time, DEAD);
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
