/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   destroy_objs.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/20 15:55:50 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/20 15:55:50 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	destroy_objs(void **objs, int size, void (*destroy)(void*))
{
	int	idx;

	idx = 0;
	while (idx < size)
	{
		destroy(objs[idx]);
		idx++;
	}
	free(objs);
}
