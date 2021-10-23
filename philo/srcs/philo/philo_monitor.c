/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_monitor.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/22 11:11:17 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/22 11:11:17 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	philo_monitor_check_sation(t_philo *philo)
{
	if (philo->eat_count >= philo->config->num_philo_must_eat)
	{
		philo->is_satiated = true;
		philo->config->num_philo_satiated++;
		if (philo->config->num_philo_satiated == philo->config->num_of_philo)
			philo->config->all_satiated = true;
	}
}

void	*philo_monitor(void *thread_data)
{
	long long	cur_time_ms;
	t_philo		*philo;

	philo = (t_philo *)thread_data;
	while (!philo->config->a_philo_died && !philo->config->all_satiated)
	{
		pthread_mutex_lock(&philo->eat_lock);
		cur_time_ms = get_time_ms();
		if ((cur_time_ms - philo->last_eat_time) > philo->config->time_to_die)
		{
			pthread_mutex_lock(&philo->config->write_lock);
			if (!philo->config->a_philo_died)
			{
				safe_write_msg(philo, HAS_DIED);
				philo->config->a_philo_died = true;
				philo->state = DEAD;
			}
			pthread_mutex_unlock(&philo->config->write_lock);
		}
		if (philo->config->num_philo_must_eat != -1 && !philo->is_satiated)
			philo_monitor_check_sation(philo);
		pthread_mutex_unlock(&philo->eat_lock);
	}
	return (NULL);
}
