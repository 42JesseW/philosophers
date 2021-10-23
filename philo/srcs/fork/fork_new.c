/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_new.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/20 15:49:26 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/20 15:49:26 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_fork	*fork_new(int idx)
{
	t_fork	*fork;

	fork = (t_fork *)malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	fork->num = idx + 1;
	if (pthread_mutex_init(&fork->lock, NULL) != 0)
	{
		free(fork);
		return (NULL);
	}
	return (fork);
}
