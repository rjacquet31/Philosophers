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

int	ft_atoi(char *str)
{
	int	i;
	int	res;
	int	sign;

	res = 0;
	i = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (res * sign < 0)
		return (0);
	else
		return (res * sign);
}

int	is_only_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

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
	return (1);
}

int	wrong_arg(char *av1, char *av2, char *av3, char *av4)
{
	if (!ft_atoi(av1) || !ft_atoi(av2) || !ft_atoi(av3) || !ft_atoi(av4))
		return (0);
	else if (!is_only_digit(av1) || !is_only_digit(av2)
		|| !is_only_digit(av3) || !is_only_digit(av4))
		return (0);
	else
		return (1);
}
