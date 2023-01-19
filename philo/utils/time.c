/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 14:51:06 by jevan-de      #+#    #+#                 */
/*   Updated: 2023/01/18 10:06:20 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/*
** Converts a {struct timeval} object it's
** members to one timestamp in milliseconds.
**
** 1 seconds = 1.000 milliseconds
** 1 seconds = 1.000.000 microseconds
*/

long long	get_time_ms(void)
{
	struct timeval	time;
	long long		ms;

	if (gettimeofday(&time, NULL) < 0)
		return (SYS_ERROR);
	ms = ((time.tv_sec * (int)1E6) + time.tv_usec) / 1000;
	return (ms);
}

int	usleep_checked(t_philosopher *philo, int time_ms)
{
	long long	wake_time;
	long long	die_time;
	long long	timestamp;

	die_time = philo->__unsafe_p_last_eaten_time \
				+ philo->p_options.time_to_die_ms;
	wake_time = get_time_ms() + time_ms;
	while (true)
	{
		usleep(100);
		timestamp = get_time_ms();
		if (timestamp >= wake_time)
			break ;
		if (timestamp >= die_time)
		{
			pthread_mutex_lock(&philo->table->lock);
			philo->table->__unsafe_someone_died = true;
			pthread_mutex_unlock(&philo->table->lock);
			return (0);
		}
	}
	return (1);
}

bool	starved(t_philosopher *philo, t_options *opts)
{
	long long	timestamp;
	long long	time_diff;

	timestamp = get_time_ms();
	pthread_mutex_lock(&philo->table->lock);
	time_diff = timestamp - philo->__unsafe_p_last_eaten_time;
	pthread_mutex_unlock(&philo->table->lock);
	return (time_diff >= opts->time_to_die_ms);
}
