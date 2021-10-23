/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_new.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/20 15:47:05 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/20 15:47:05 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_philo	*philo_new(int idx, t_config *config)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->num = idx + 1;
	philo->eat_count = 0;
	philo->is_satiated = false;
	philo->state = THINKING;
	philo->config = config;
	philo->last_eat_time = get_time_ms();
	if (pthread_create(&(philo->main_tid), NULL, &philo_run, philo) != 0
		|| pthread_mutex_init(&philo->eat_lock, NULL) != 0)
	{
		free(philo);
		return (NULL);
	}
	return (philo);
}
