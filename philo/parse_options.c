/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_options.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 10:17:10 by jevan-de      #+#    #+#                 */
/*   Updated: 2023/01/17 16:38:47 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static bool	is_valid_number(char *arg)
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

int	parse_options(int argc, char *argv[], t_options *options)
{
	int		idx;

	if (argc < 5 || argc > 6)
		return (0);
	idx = 1;
	while (argv[idx])
	{
		if (!is_valid_number(argv[idx]))
			return (0);
		idx++;
	}
	options->philosopher_amount = ft_atoi(argv[1]);
	if (options->philosopher_amount == 0)
		return (0);
	options->time_to_die_ms = ft_atoi(argv[2]);
	options->time_to_eat_ms = ft_atoi(argv[3]);
	options->time_to_sleep_ms = ft_atoi(argv[4]);
	options->must_eat_amount = MISSING_OPTION;
	if (argc == 6)
		options->must_eat_amount = ft_atoi(argv[5]);
	options->start_time = get_time_ms();
	return (1);
}
