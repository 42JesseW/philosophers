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

/*
** When creating a philosopher, sleep for a small
** amount of time to make sure the order of eating
** is enforced. The startup order forces the philosophers
** to eat in their own groups preventing one from dying
** in cases like "4 410 200 200 10".
*/

t_philo	**config_init_philos(t_config *config)
{
	t_philo		**philos;
	int			idx;

	philos = (t_philo **)malloc(sizeof(t_philo *) * config->num_of_philo);
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
		usleep(1000);
		idx++;
	}
	return (philos);
}
