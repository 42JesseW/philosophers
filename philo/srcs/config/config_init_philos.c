/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   config_initphilos.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/20 15:52:38 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/20 15:52:38 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_philo	**config_init_philos(t_config *config)
{
	t_philo		**philos;
	int			idx;

	philos = (t_philo **)malloc(sizeof(t_philo *) * config->num_of_philo + 1);
	if (!philos)
		return (NULL);
	idx = 0;
	while (idx < config->num_of_philo)
	{
		philos[idx] = philo_new(idx, config);
		if (!philos[idx])
		{
			while (idx >= 0)
			{
				philo_destroy((void *)philos[idx]);
				idx--;
			}
		}
		idx++;
	}
	philos[idx] = NULL;
	return (philos);
}
