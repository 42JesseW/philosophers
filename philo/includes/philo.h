/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/11 20:09:23 by jevan-de      #+#    #+#                 */
/*   Updated: 2022/05/11 20:09:23 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# define ARG_ERROR 		"Program requires at least 4 integer arguments"
# define SYS_ERROR		(-1)
# define PARSE_ERROR	(-1)
# define SUCCESS 		1
# define MISSING_OPTION	0

# define Y "\033[33m"
# define W "\033[0m"

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>

enum	e_state
{
	FORK = 0,
	EATING,
	SLEEPING,
	THINKING,
	DEAD
};

typedef struct s_config
{
	pthread_mutex_t	log_lock;
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_philo_must_eat;
	int				num_of_forks;
	int				num_philo_satiated;
}	t_config;

/*
 * should log one of the following:
 *	- timestamp_in_ms X has taken a fork
 *	- timestamp_in_ms X is eating
 *	- timestamp_in_ms X is sleeping
 *	- timestamp_in_ms X is thinking
 *	- timestamp_in_ms X died
 *
 *	Where timestamp_in_ms is the current time in ms
 *	and X the number of the philosopher.
 */

int		log_state(t_config *config, int philo_number, enum e_state state);

int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
long	ft_atol(const char *str);
int		ft_isdigit(int c);

#endif
