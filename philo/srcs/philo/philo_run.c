/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_thread_func.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/20 15:47:37 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/20 15:47:37 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*philo_run(void *thread_data)
{
	t_philo	*philo;

	philo = (t_philo *)thread_data;
	if (pthread_create(&(philo->monitor_tid), NULL, &philo_monitor, philo) != 0)
		return (NULL);
	while (!philo->config->a_philo_died && !philo->config->all_satiated)
	{
		if (philo->state == THINKING && philo_eat(philo) != 1)
			break ;
		if (philo->state == EATING && philo_sleep(philo) != 1)
			break ;
		if (philo->state == SLEEPING && philo_think(philo) != 1)
			break ;
	}
	pthread_join(philo->monitor_tid, NULL);
	return (NULL);
}
