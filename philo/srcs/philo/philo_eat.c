/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_eat.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/23 08:14:55 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/23 08:14:55 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/*
** DEADLOCK
** - To prevent deadlock in the following situation:
**	 '+' = philosopher	'#' = fork
**	 	              +
**		            / # \
**		           /#   #\
**		          +-------+
**	 Where each philosopher is able to pick up one fork
**	 and therefore all philosophers wait for a right fork,
**	 the following logic is used.
**
**	 Based on the number of the philosopher, even or uneven,
**	 it is decided which fork, left or right, is picked up
**	 first. In the above example this would be something like
**	 the following:
**
**		- [philo_1 tries to pick up its first fork](left)	-> (v)
**		- [philo_2 tries to pick up its first fork](right)	-> (x)
**															-> locked by philo_1
**		- [philo_3 tries to pick up its first fork](left)	-> (v)
**		- [philo_1 tries to pick up its second fork](right)	-> (x)
**															-> locked by philo_3
**		- [philo_2 WAITING FOR LOCK]
**		- [philo_3 tries to pick up its second fork](right)	-> (v)
**															-> STARTS EATING
**		- [philo_1 WAITING FOR LOCK]
**		- [philo_2 WAITING FOR LOCK]
**		- [philo_3 FINISHED EATING]
**		- [philo_1 tries to pick up its second fork](right)	-> (v)
**															-> STARTS EATING
**		- [philo_2 WAITING FOR LOCK]
**		- [philo_3 tries to pick up its first fork](left)	-> (x)
**															-> locked by philo_1
**		- ...
**
** LOCK
** - A philosopher can not die when it's eating.
*/

static t_fork	*use_fork(t_philo *philo, bool first, bool lock)
{
	t_fork	*fork;
	int		idx[2];

	idx[0] = philo->num - 2;
	if (philo->num == 1)
		idx[0] = philo->config->num_of_forks - 1;
	idx[1] = philo->num - 1;
	if (first && (philo->num % 2) == 1)
		fork = philo->config->forks[idx[0]];
	if (first && (philo->num % 2) == 0)
		fork = philo->config->forks[idx[1]];
	if (!first && (philo->num % 2) == 1)
		fork = philo->config->forks[idx[1]];
	if (!first && (philo->num % 2) == 0)
		fork = philo->config->forks[idx[0]];
	if (lock && pthread_mutex_lock(&fork->lock) != 0)
		return (NULL);
	if (lock && !philo->config->a_philo_died && !philo->config->all_satiated)
		safe_write_msg(philo, TAKEN_FORK);
	if (!lock && pthread_mutex_unlock(&fork->lock) != 0)
		return (NULL);
	return (fork);
}

/*
** A mutex is used to prevent the monitoring thread
** from letting the philosopher die while its eating.
*/

int	philo_eat(t_philo *philo)
{
	if (!use_fork(philo, true, true) || !use_fork(philo, false, true))
		return (SYS_ERROR);
	philo->state = EATING;
	pthread_mutex_lock(&philo->eat_lock);
	if (!philo->config->a_philo_died && !philo->config->all_satiated)
	{
		safe_write_msg(philo, IS_EATING);
		if (usleep(philo->config->time_to_eat * 1000) < 0)
			return (SYS_ERROR);
		philo->last_eat_time = get_time_ms();
		philo->eat_count++;
	}
	if (!use_fork(philo, true, false) || !use_fork(philo, false, false))
		return (SYS_ERROR);
	pthread_mutex_unlock(&philo->eat_lock);
	return (1);
}
