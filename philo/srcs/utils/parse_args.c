/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/20 13:53:30 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/20 13:53:30 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	parse_args(int argc, char *argv[], t_config *config)
{
	int		idx;

	if (argc < 5 || argc > 6)
		return (false);
	idx = 1;
	while (argv[idx])
	{
		if (!is_valid_number(argv[idx]))
			return (false);
		idx++;
	}
	config->num_of_philo = ft_atoi(argv[1]);
	config->time_to_die = ft_atoi(argv[2]);
	config->time_to_eat = ft_atoi(argv[3]);
	config->time_to_sleep = ft_atoi(argv[4]);
	config->num_philo_must_eat = MISSING_OPTION;
	if (argc == 6)
		config->num_philo_must_eat = ft_atoi(argv[5]);
	return (true);
}
