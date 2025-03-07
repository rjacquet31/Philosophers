/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:11:00 by rafael            #+#    #+#             */
/*   Updated: 2025/03/04 10:11:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	process_status(t_philo *philo, time_t ts, t_status new)
{
	int	running;

	philo->status = new;
	pthread_mutex_lock(&philo->table->m_print);
	pthread_mutex_lock(&philo->table->m_simulation);
	running = philo->table->sim_running;
	pthread_mutex_unlock(&philo->table->m_simulation);
	if (running || philo->status == DEAD)
	{
		if (philo->status == DEAD)
			printf("%ld %d died\n", ts, (philo->id) + 1);
		else if (philo->status == EATING)
			printf("%ld %d is eating\n", ts, (philo->id) + 1);
		else if (philo->status == SLEEPING)
			printf("%ld %d is sleeping\n", ts, (philo->id) + 1);
		else if (philo->status == THINKING)
			printf("%ld %d is thinking\n", ts, (philo->id) + 1);
		else if (philo->status == LEFT_FORK || philo->status == RIGHT_FORK)
			printf("%ld %d has taken a fork\n", ts, (philo->id) + 1);
	}
	pthread_mutex_unlock(&philo->table->m_print);
}
