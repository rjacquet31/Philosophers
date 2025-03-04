/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:56:39 by rafael            #+#    #+#             */
/*   Updated: 2025/02/26 10:56:39 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	free_all(t_phil*philos, t_fork *forks, int exit_code)
{
	free(philos);
	free(forks);
	return (exit_code);
}

int	main(int argc, char **argv)
{
	t_params	params;
	t_phil		*philos;
	t_fork		*forks;

	if (!wrong_arg(argv[1], argv[2], argv[3], argv[4]))
		return (wrong_format());
	if (!init_params(&params, argc, argv))
		return (free_all(NULL, NULL, 1));
	if (!create_philos(&philos, &forks, &params))
		return (free_all(NULL, NULL, 1));
	if (!create_threads(philos, &params))
		return (free_all(philos, forks, 1));
	if (!wait_threads(philos, &params))
		return (free_all(philos, forks, 1));
	return (free_all(philos, forks, 0));
}
