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

int	main(int ac, char **av)
{
	t_table	*table;

	table = NULL;
	if (check_input(ac, av) == ERROR)
	{
		wrong_format();
		return (process_exit(1, table, "Invalid arguments: check count/types"));
	}
	table = init_program(ac, av);
	if (!table)
		return (process_exit(1, table, "Error while initializing the program"));
	if (start_simulation(table) == ERROR)
		return (process_exit(2, table, "Error while threading the philosophy"));
	if (stop_simulation(table) == ERROR)
		return (process_exit(2, table, "Error while stopping the simulation"));
	return (process_exit(SUCCESS, table, NULL));
}
