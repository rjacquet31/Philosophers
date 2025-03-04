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

void	print_status(t_phil *phil, char *status)
{
	pthread_mutex_lock(&(phil->params->m_output));
	if (phil->params->end)
	{
		pthread_mutex_unlock(&(phil->params->m_output));
		return ;
	}
	printf("%ld %d %s\n", get_time_in_ms() - phil->params->start_time, phil->pos + 1, status);
	pthread_mutex_unlock(&(phil->params->m_output));
}
