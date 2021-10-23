/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/21 08:20:33 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/21 08:20:33 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

# define MISSING_OPTION -1
# define SYS_ERROR -1
# define MAX_LONG_LEN 20
# define ERR "Invalid arguments: program requires at least 4 integer arguments\n"

enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD
};

enum e_msg
{
	TAKEN_FORK = 0,
	IS_EATING,
	IS_SLEEPING,
	IS_THINKING,
	HAS_DIED
};

typedef struct s_fork
{
	int				num;
	pthread_mutex_t	lock;
}	t_fork;

typedef struct s_config
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_philo_must_eat;
	int				num_of_forks;
	int				num_philo_satiated;
	bool			a_philo_died;
	bool			all_satiated;
	long long		start_time;
	t_fork			**forks;
	pthread_mutex_t	write_lock;
}	t_config;

typedef struct s_philo
{
	int				num;
	int				eat_count;
	long long		last_eat_time;
	bool			is_satiated;
	enum e_state	state;
	pthread_mutex_t	eat_lock;
	pthread_t		monitor_tid;
	pthread_t		main_tid;
	t_config		*config;
}	t_philo;

int					ft_isdigit(int c);
size_t				ft_strlen(const char *s);
long				ft_atol(const char *str);
int					ft_atoi(const char *str);

ssize_t				safe_write_msg(t_philo *philo, enum e_msg type);
ssize_t				safe_write_msg_long(long timestamp);
void				destroy_objs(void **objs, int size, void (*destroy)(void*));
bool				parse_args(int argc, char *argv[], t_config *config);
bool				is_valid_number(char *arg);
long long			get_time_ms(void);

t_philo				*philo_new(int idx, t_config *config);
void				philo_destroy(void *obj);
void				*philo_run(void *thread_data);
void				*philo_monitor(void *thread_data);
int					philo_eat(t_philo *philo);
int					philo_sleep(t_philo *philo);
int					philo_think(t_philo *philo);

void				fork_destroy(void *obj);
t_fork				*fork_new(int idx);

bool				config_init(t_config *config);
void				config_print(t_config *config);
void				config_destroy(t_config *config, t_philo **philos);
t_fork				**config_init_forks(t_config *config);
t_philo				**config_init_philos(t_config *config);

#endif
