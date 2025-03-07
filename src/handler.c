/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:01:20 by rafael            #+#    #+#             */
/*   Updated: 2025/02/27 10:01:20 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	wrong_format(void)
{
	printf(RED "Erreur : Mauvaise utilisation du programme.\n" RESET);
	printf(YELLOW "Utilisation correcte :\n" RESET);
	printf("./philo number_of_philosophers ");
	printf("time_to_die time_to_eat time_to_sleep\n\n");
	printf(YELLOW "Arguments :\n" RESET);
	printf("  - " YELLOW "number_of_philosophers" );
	printf(RESET " : Nombre de philosophes (exemple : 5)\n");
	printf("  - " YELLOW "time_to_die" );
	printf(RESET " : Temps max sans manger avant de mourir (en ms)\n");
	printf("  - " YELLOW "time_to_eat" );
	printf(RESET " : Temps nécessaire pour manger (en ms)\n");
	printf("  - " YELLOW "time_to_sleep" );
	printf(RESET " : Temps de sommeil après avoir mangé (en ms)\n");
	return (ERROR);
}

int	digits(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_input(int ac, char **av)
{
	size_t	i;
	int		nb;

	i = 0;
	if (ac - 1 < 4 || ac - 1 > 5)
		return (ERROR);
	if (digits(av[1]) == 0 || digits(av[2]) == 0
		|| digits(av[3]) == 0 || digits(av[4]) == 0)
		return (ERROR);
	while ((int)++i < ac)
	{
		nb = ft_atoi(av[i]);
		if ((i == 1 && nb < 1) || (i == 2 && nb < 1)
			|| (i != 1 && nb < 0) || nb > INT_MAX)
			return (ERROR);
	}
	return (SUCCESS);
}
