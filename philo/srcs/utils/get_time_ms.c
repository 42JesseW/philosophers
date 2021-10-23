/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_time_ms.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/22 11:14:42 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/22 11:14:42 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/*
** Converts a {struct timeval} object it's
** members to one timestamp in milliseconds.
**
** 1 seconds = 1.000 milliseconds
** 1 seconds = 1.000.000 microseconds
*/

long long	get_time_ms(void)
{
	struct timeval	time;
	long long		ms;

	if (gettimeofday(&time, NULL) < 0)
		return (-1);
	ms = ((time.tv_sec * (int)1E6) + time.tv_usec) / 1000;
	return (ms);
}
