/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strlen.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 10:09:57 by jevan-de      #+#    #+#                 */
/*   Updated: 2023/01/09 10:28:17 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

size_t	ft_strlen(const	char *str)
{
	int	count;
	int	idx;

	idx = 0;
	count = 0;
	while (str[idx])
	{
		count++;
		idx++;
	}
	return (count);
}
