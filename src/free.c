/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:11:58 by rafael            #+#    #+#             */
/*   Updated: 2025/03/07 14:11:58 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_table(t_table *table)
{
	size_t	i;

	if (!table)
		return ;
	if (table->m_forks != NULL)
		free(table->m_forks);
	if (table->philos != NULL)
	{
		i = -1;
		while (++i < table->nb_philo)
		{
			if (table->philos[i] != NULL)
				free(table->philos[i]);
		}
		free(table->philos);
	}
	free(table);
}

void	destroy_mutexes(t_table *table)
{
	size_t	i;

	i = -1;
	while (++i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->m_forks[i]);
		pthread_mutex_destroy(&table->philos[i]->m_meal);
	}
	pthread_mutex_destroy(&table->m_print);
	pthread_mutex_destroy(&table->m_simulation);
}

int	process_exit(int exit_id, t_table *table, char *msg)
{
	if (table != NULL)
	{
		destroy_mutexes(table);
		free_table(table);
	}
	if (exit_id > 0 && msg)
		printf("%s\n", msg);
	return (exit_id);
}
