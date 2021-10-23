/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_destroy.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/20 15:48:06 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/20 15:48:06 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	philo_destroy(void *obj)
{
	t_philo	*philo;

	philo = (t_philo *)obj;
	if (philo->state != DEAD && !philo->config->all_satiated)
		pthread_detach(philo->main_tid);
	pthread_mutex_destroy(&philo->eat_lock);
	free(philo);
}
