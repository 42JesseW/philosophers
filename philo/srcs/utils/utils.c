/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/11 20:09:21 by jevan-de      #+#    #+#                 */
/*   Updated: 2022/05/11 20:09:21 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*state_messages[] = {
	" has taken a fork",
	" is eating",
	" is sleeping",
	" is thinking",
	" died"
};

time_t	get_current_time_ms(void)
{
	struct timeval	time;
	long long		ms;

	gettimeofday(&time, NULL);
	ms = ((time.tv_sec * (int)1E6) + time.tv_usec) / 1000;
	return (ms);
}

int		log_state(t_config *config, int philo_number, enum e_state state)
{
	time_t	timestamp;

	if (pthread_mutex_lock(&config->log_lock) == SYS_ERROR)
		return (SYS_ERROR);
	timestamp = get_current_time_ms();
	printf("[%s%li%s] %d %s\n", Y, timestamp, W, philo_number, state_messages[state]);
	if (pthread_mutex_unlock(&config->log_lock) == SYS_ERROR)
		return (SYS_ERROR);
	return (SUCCESS);
}
