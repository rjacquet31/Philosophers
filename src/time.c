/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:27:50 by rafael            #+#    #+#             */
/*   Updated: 2025/02/26 11:27:50 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

time_t	get_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

time_t	get_ts(t_philo *philo)
{
	return (get_ms() - philo->table->start_time);
}

int	ft_msleep(unsigned long milliseconds)
{
	struct timeval	start;
	struct timeval	current;
	unsigned long	elapsed;

	if (!milliseconds)
		return (-1);
	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(200);
		gettimeofday(&current, NULL);
		elapsed = ((current.tv_sec - start.tv_sec) * 1000)
			+ ((current.tv_usec - start.tv_usec) / 1000);
		if (elapsed >= milliseconds)
			break ;
	}
	return (0);
}
