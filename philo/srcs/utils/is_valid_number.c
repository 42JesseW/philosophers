/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_valid_number.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/20 13:52:32 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/20 13:52:32 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	is_valid_number(char *arg)
{
	long	num;
	int		idx;

	if (!arg || !(*arg))
		return (false);
	idx = 0;
	while (arg[idx])
	{
		if (!ft_isdigit(arg[idx]))
			return (false);
		num = ft_atol(arg);
		if (num < INT_MIN || num > INT_MAX)
			return (false);
		idx++;
	}
	return (true);
}
