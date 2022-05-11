/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/11 20:00:17 by jevan-de      #+#    #+#                 */
/*   Updated: 2022/05/11 20:00:17 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

// TODO write test cases
bool	is_valid_number(char *arg)
{
	long	num;
	int		idx;

	if (!arg || !(*arg))
		return (false);
	idx = 0;
	while (arg[idx])
	{
		if (!ft_isdigit(arg[idx]))
			return (false);
		num = ft_atol(arg);
		if (num < INT_MIN || num > INT_MAX)
			return (false);
		idx++;
	}
	return (true);
}

// TODO write test cases
int 	parse_args(int argc, char *argv[], t_config *config)
{
	int		idx;

	if (argc < 5 || argc > 6)
		return (PARSE_ERROR);
	idx = 1;
	while (argv[idx])
	{
		if (!is_valid_number(argv[idx]))
			return (PARSE_ERROR);
		idx++;
	}
	config->num_of_philo = ft_atoi(argv[1]);
	config->time_to_die = ft_atoi(argv[2]);
	config->time_to_eat = ft_atoi(argv[3]);
	config->time_to_sleep = ft_atoi(argv[4]);
	config->num_philo_must_eat = MISSING_OPTION;
	if (argc == 6)
		config->num_philo_must_eat = ft_atoi(argv[5]);
	return (SUCCESS);
}

/*
** [Philosophers]
**
**	DESCRIPTION
**	- 1 to {number_of_philosophers} philosophers sit around
**	  a table with a bowl of spaghetti in the middle. They
**	  share forks to eat go into the following states in turn.
**		- [Order of states]
**			1. (starting state) THINKING
**			2. EATING
**			3. SLEEPING
**
**	  While in the THINKING state, they wait for two forks to
**	  become available. When these are available, they go into
**	  the EATING state for {time_to_eat} amount of milliseconds.
**
**	  When they're done eating, they go into the SLEEPING state
**	  for {time_to_sleep} amount of milliseconds.
**
**	  If a philosopher doesn't start eating {time_to_die} seconds
**	  after starting his last meal (or the beginning of the
**	  simulation), he dies, and goes into the DEAD state.
**
**	  At this point the simulation stops and all threads exit.
**
**	EDGE CASES
**	- DEATH during SLEEPING state.
**	- DEATH during EATING state, can not die.
**	- {number_of_philosophers} is 1, which means there's only 1 fork
**	  and the philosopher will always die because it can't lock two forks.
**	- {number_of_times_each_philosopher_must_eat} is not reached
**	  by all philosophers at the same time.
**	- Dead lock when each philosopher locks one fork and no-one can eat.
**
**	IMPLEMENTATION
**	- For each philosopher a thread is created, together with a
**	  monitoring thread that watches the state of the philosopher
**	  its monitoring. The monitoring thread watches the state of
**	  its philosopher for two occurrences:
**		1. DEATH
**			- If a philosopher doesn't start eating {time_to_die} milliseconds
**			  after starting his last meal or the beginning of the simulation,
**			  it is marked as dead by the monitoring thread.
**		2. SATIATED
**			- If a philosopher has eaten {number_of_times_each_philosopher_must_eat}
**			  it is marked as SATIATED by the monitoring thread.
**
**
**	REQUIREMENTS
**	1. Each philosopher should be given a number
**	   from 1 to ’number_of_philosophers’.				(v)
**		- {t_philo}.num
**	2. Each philosopher should be a thread.				(v)
**		- {t_philo}.main_tid
**	3. Each time a philosopher has finished eating, he
**	   will drop his forks and start sleeping
**	4. The status printed should not be scrambled or
**	   intertwined with another philosopher’s status.	(v)
**		- {safe_write_msg()} with mutex lock and {hold}
**		  if no more writing is allowed after a death
**
**	ALLOWED
**	- string.memset
**	- stdio.printf
**	- stdlib.malloc
**	- stdlib.free
**	- unistd.write
**	- unistd.usleep
**	- sys/time.gettimeofday
**	- pthread.pthread_create
**	- pthread.pthread_detach
**	- pthread.pthread_join
**	- pthread.pthread_mutex_init
**	- pthread.pthread_mutex_destroy
**	- pthread.pthread_mutex_lock
**	- pthread.pthread_mutex_unlock
**
**	ARGUMENTS
**	- REQUIRED number_of_philosophers
**	- REQUIRED time_to_die
**	- REQUIRED time_to_eat
**	- REQUIRED time_to_sleep
**	- OPTIONAL [number_of_times_each_philosopher_must_eat]
**
**	- {argv[1]}(number_of_philosophers):
**	  Represents the number of philosophers and
**	  also the number of forks.
**
**	- {argv[2]}(time_to_die):
**	  is in milliseconds, if a philosopher does not
**	  start eating ’time_to_die’ milliseconds after
**	  starting his last meal or the beginning of
**	  the simulation, it dies
**
**	- {argv[3]}(time_to_eat):
**	  is in milliseconds and is the time it takes
**	  for a philosopher to eat. During that time he
**	  will need to keep the two forks.
**
**	- {argv[4]}(time_to_sleep):
**	  is in milliseconds and is the time the
**	  philosopher will spend sleeping.
**
**	- {argv[5]}(number_of_times_each_philosopher_must_eat):
**	  argument is optional, if all philosophers eat
**	  at least ’number_of_times_each_philosopher_must_eat’
**	  the simulation will stop. If not specified, the
**	  simulation will stop only at the death of a philosopher
*/

int	main(int argc, char *argv[])
{
	t_config	config;

	if (parse_args(argc, argv, &config) == SYS_ERROR)
	{
		printf("%s\n", ARG_ERROR);
		return (EXIT_FAILURE);
	}
	log_state(&config, 1, DEAD);
	return (EXIT_SUCCESS);
}
