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

// libraries
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

// defines
# define TRUE 1
# define FALSE 0
# define ERROR -1
# define NULL_ERROR 0
# define SUCCESS 0
# define RED     "\033[1;31m"
# define YELLOW  "\033[1;33m"
# define RESET   "\033[0m"

// struct
typedef enum e_status
{
	DEAD = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	LEFT_FORK = 4,
	RIGHT_FORK = 5
}			t_status;

typedef struct s_philo	t_philo;

typedef struct s_table
{
	size_t			nb_philo;
	time_t			start_time;
	int				sim_running;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				min_nb_meal;
	t_philo			**philos;
	pthread_t		monitoring;
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_simulation;
}				t_table;

typedef struct s_philo
{
	int				id;
	int				fork[2];
	int				nb_meal;
	time_t			last_meal;
	t_status		status;
	pthread_t		thread;
	pthread_mutex_t	m_meal;
	struct s_table	*table;
}				t_philo;
// algo.c
void				*dead(t_philo *philo);
void				start_eating_then_sleeping(t_philo *philo);
void				start_thinking(t_philo *philo);
// free.c
void				free_table(t_table *table);
void				destroy_mutexes(t_table *table);
int					process_exit(int exit_id, t_table *table, char *msg);
// handler.c
int					wrong_format(void);
int					check_input(int ac, char **av);
// init.c
t_table				*init_program(int ac, char **av);
t_philo				**init_philosophers(t_table *table);
pthread_mutex_t		*init_forks(t_table *table);
int					init_global_mutexes(t_table *table);
void				assign_forks(t_philo *philo);
// monitoring.c
void				*monitor_philosophers(void *table);
int					is_simulation_running(t_philo *philo);
int					is_someone_dead(t_philo *philo);
void				set_simulation_status(t_table *table, int status);
int					is_end_of_dinner(t_table *table);
// output.c
void				process_status(t_philo *philo, time_t ts, t_status new);
// sim.c
int					start_simulation(t_table *table);
int					stop_simulation(t_table *table);
void				*run_philosophy(void *philo);
// time.c
time_t				get_ms(void);
time_t				get_ts(t_philo *philo);
int					ft_msleep(unsigned long milliseconds);
// utils.c
int					ft_atoi(const char *str);

#endif