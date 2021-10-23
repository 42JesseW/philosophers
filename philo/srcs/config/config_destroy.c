/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   config_destroy.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/20 15:55:01 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/20 15:55:01 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	config_destroy(t_config *config, t_philo **philos)
{
	int		obj_amount;

	obj_amount = config->num_of_philo;
	if (config->forks)
		destroy_objs((void **)config->forks, obj_amount, fork_destroy);
	pthread_mutex_destroy(&config->write_lock);
	if (philos)
		destroy_objs((void **)philos, obj_amount, philo_destroy);
}
