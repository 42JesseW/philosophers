/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   config_init.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/20 15:52:09 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/20 15:52:09 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	config_init(t_config *config)
{
	config->a_philo_died = false;
	config->all_satiated = false;
	config->num_of_forks = config->num_of_philo;
	config->forks = config_init_forks(config);
	if (!config->forks)
		return (false);
	if (pthread_mutex_init(&config->write_lock, NULL) != 0)
	{
		config_destroy(config, NULL);
		return (false);
	}
	config->num_philo_satiated = 0;
	config->start_time = get_time_ms();
	return (true);
}
