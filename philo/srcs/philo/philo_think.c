/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_think.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/23 08:15:47 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/23 08:15:47 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	philo_think(t_philo *philo)
{
	if (simulation_has_ended(philo->config, BOTH))
		return (1);
	safe_write_msg(philo, IS_THINKING);
	philo->state = THINKING;
	return (1);
}
