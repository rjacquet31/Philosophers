/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:01:33 by rafael            #+#    #+#             */
/*   Updated: 2025/02/27 10:01:33 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_table	*init_program(int ac, char **av)
{
	t_table	*table;

	table = malloc(sizeof(t_table) * 1);
	if (!table)
		return (NULL_ERROR);
	table->nb_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->min_nb_meal = -1;
	if (ac == 6)
		table->min_nb_meal = ft_atoi(av[5]);
	table->philos = init_philosophers(table);
	if (!table->philos)
		return (NULL_ERROR);
	if (!init_global_mutexes(table))
		return (NULL_ERROR);
	table->sim_running = FALSE;
	return (table);
}

t_philo	**init_philosophers(t_table *table)
{
	t_philo			**philos;
	unsigned int	i;

	philos = malloc(sizeof(t_philo) * table->nb_philo);
	if (!philos)
		return (NULL_ERROR);
	i = 0;
	while (i < table->nb_philo)
	{
		philos[i] = malloc(sizeof(t_philo) * 1);
		if (!philos[i])
			return (NULL_ERROR);
		if (pthread_mutex_init(&philos[i]->m_meal, 0) != 0)
			return (NULL_ERROR);
		philos[i]->table = table;
		philos[i]->id = i;
		philos[i]->nb_meal = 0;
		philos[i]->last_meal = 0;
		philos[i]->status = THINKING;
		assign_forks(philos[i]);
		i++;
	}
	return (philos);
}

pthread_mutex_t	*init_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	size_t			i;

	forks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!forks)
		return (NULL_ERROR);
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (NULL_ERROR);
		i++;
	}
	return (forks);
}

int	init_global_mutexes(t_table *table)
{
	table->m_forks = init_forks(table);
	if (!table->m_forks)
		return (FALSE);
	if (pthread_mutex_init(&table->m_simulation, 0) != 0)
		return (ERROR);
	if (pthread_mutex_init(&table->m_print, 0) != 0)
		return (ERROR);
	return (TRUE);
}

void	assign_forks(t_philo *philo)
{
	philo->fork[0] = philo->id;
	philo->fork[1] = (philo->id + 1) % philo->table->nb_philo;
	if (philo->id % 2)
	{
		philo->fork[0] = (philo->id + 1) % philo->table->nb_philo;
		philo->fork[1] = philo->id;
	}
}
