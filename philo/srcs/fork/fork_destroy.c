/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_destroy.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/20 15:49:50 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/20 15:49:50 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	fork_destroy(void *obj)
{
	t_fork	*fork;

	fork = (t_fork *)obj;
	if (fork)
		pthread_mutex_destroy(&fork->lock);
	free(fork);
}
