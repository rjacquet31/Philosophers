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

	table = (t_table *)malloc(sizeof(t_table));
	if (table == NULL)
		return (NULL_ERROR);
	table->nb_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->min_nb_meal = -1;
	if (ac == 6)
		table->min_nb_meal = ft_atoi(av[5]);
	table->sim_running = FALSE;
	table->philos = init_philosophers(table);
	if (table->philos == NULL)
		return (NULL_ERROR);
	if (!init_global_mutexes(table))
		return (NULL_ERROR);
	return (table);
}

t_philo	**init_philosophers(t_table *table)
{
	t_philo			**philos;
	unsigned int	index;

	philos = (t_philo **)malloc(sizeof(t_philo *) * table->nb_philo);
	if (philos == NULL)
		return (NULL_ERROR);
	index = 0;
	while (index < table->nb_philo)
	{
		philos[index] = (t_philo *)malloc(sizeof(t_philo));
		if (philos[index] == NULL)
			return (NULL_ERROR);
		if (pthread_mutex_init(&philos[index]->m_meal, NULL) != 0)
			return (NULL_ERROR);
		philos[index]->table = table;
		philos[index]->id = index;
		philos[index]->nb_meal = 0;
		philos[index]->last_meal = 0;
		philos[index]->status = THINKING;
		assign_forks(philos[index]);
		index++;
	}
	return (philos);
}

pthread_mutex_t	*init_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	size_t			i;

	forks = (pthread_mutex_t *)malloc(
			sizeof(pthread_mutex_t) * table->nb_philo);
	if (forks == NULL)
		return (NULL_ERROR);
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (NULL_ERROR);
		i++;
	}
	return (forks);
}

int	init_global_mutexes(t_table *table)
{
	table->m_forks = init_forks(table);
	if (table->m_forks == NULL)
		return (FALSE);
	if (pthread_mutex_init(&table->m_simulation, NULL) != 0)
		return (ERROR);
	if (pthread_mutex_init(&table->m_print, NULL) != 0)
		return (ERROR);
	return (TRUE);
}

void	assign_forks(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id;
	right_fork = (philo->id + 1) % philo->table->nb_philo;
	if (philo->id % 2 == 0)
	{
		philo->fork[0] = left_fork;
		philo->fork[1] = right_fork;
	}
	else
	{
		philo->fork[0] = right_fork;
		philo->fork[1] = left_fork;
	}
}
