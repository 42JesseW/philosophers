/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 10:02:51 by jevan-de      #+#    #+#                 */
/*   Updated: 2023/01/18 10:07:30 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H
# define SYS_ERROR		(-1)
# define MISSING_OPTION (-1)
# define TIME_UNSET		(-1)
# define MAX_LONG_LEN	20

# include <stdbool.h>
# include <limits.h>

# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>

enum e_msg
{
	TAKEN_FORK = 0,
	IS_EATING,
	IS_SLEEPING,
	IS_THINKING,
	HAS_DIED
};

/*
** Arguments passed to the program.
*/
typedef struct s_options
{
	int			philosopher_amount;
	int			time_to_die_ms;
	int			time_to_eat_ms;
	int			time_to_sleep_ms;
	int			must_eat_amount;
	long long	start_time;
}	t_options;

typedef struct s_fork
{
	pthread_mutex_t	lock;
}	t_fork;

typedef struct s_table
{
	t_fork			*forks;
	int				fork_amount;
	int				__unsafe_saturated_count;
	bool			__unsafe_allowed_to_write;
	bool			__unsafe_someone_died;
	bool			__unsafe_all_saturated;
	pthread_mutex_t	lock;
}	t_table;

typedef struct s_philosopher
{
	int				p_number;
	t_options		p_options;
	int				p_eaten_amount;
	long long		__unsafe_p_last_eaten_time;	

	bool			is_saturated;
	t_fork			*forks[2];
	t_table			*table;
	pthread_t		thread_id;
}	t_philosopher;

typedef struct s_watcher
{
	t_philosopher	*philos;
	t_table			*table;
	t_options		opts;
	pthread_t		thread_id;
}	t_watcher;

int				ft_atoi(const char *str);
long			ft_atol(const char *str);
size_t			ft_strlen(const char *str);
int				ft_isdigit(int c);

int				init_table(t_table *table, int fork_amount);
void			destroy_table(t_table *table);

void			*philosophize(void *_philo);
int				start_philosophers(t_philosopher *philos, int amount);
t_philosopher	*init_philosophers(t_options *options, t_table *table);

int				start_watcher(t_watcher *watcher);
void			init_watcher(t_watcher *watcher, t_philosopher *philos,
					t_table *table, t_options *opts);
void			*watch(void *_watcher);

long long		get_time_ms(void);
int				usleep_checked(t_philosopher *philo, int time_ms);
ssize_t			safe_write_msg(t_philosopher *philo, enum e_msg type);

int				start_sleeping(t_philosopher *philo);
int				start_eating(t_philosopher *philo);
bool			done(t_philosopher *philo);

bool			starved(t_philosopher *philo, t_options *opts);
int				parse_options(int argc, char *argv[], t_options *options);

#endif
