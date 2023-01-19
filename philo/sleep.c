/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sleep.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/17 18:10:32 by jevan-de      #+#    #+#                 */
/*   Updated: 2023/01/17 18:10:46 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	start_sleeping(t_philosopher *philo)
{
	safe_write_msg(philo, IS_SLEEPING);
	return (usleep_checked(philo, philo->p_options.time_to_sleep_ms));
}
