/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   config_init_forks.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/20 15:54:03 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/20 15:54:03 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_fork	**config_init_forks(t_config *config)
{
	t_fork	**forks;
	int		idx;

	forks = (t_fork **)malloc(sizeof(t_fork *) * config->num_of_forks + 1);
	if (!forks)
		return (NULL);
	idx = 0;
	while (idx < config->num_of_forks)
	{
		forks[idx] = fork_new(idx);
		if (!forks[idx])
		{
			while (idx >= 0)
			{
				fork_destroy((void *)forks[idx]);
				idx--;
			}
		}
		idx++;
	}
	forks[idx] = NULL;
	return (forks);
}
