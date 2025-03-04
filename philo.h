/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:39:10 by rafael            #+#    #+#             */
/*   Updated: 2025/02/26 10:39:10 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define RED     "\033[1;31m"
# define YELLOW  "\033[1;33m"
# define RESET   "\033[0m"

// Librairies
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>

// struct
typedef struct s_philosopher
{
    int id;
    pthread_t thread;
    pthread_mutex_t *fork;
}   t_philosopher;

typedef enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}   t_state;
// main.c

// handler.c
int		wrong_format(void);
int		wrong_arg(char *av1, char *av2, char *av3, char *av4);
// utils.c

// free.c

#endif