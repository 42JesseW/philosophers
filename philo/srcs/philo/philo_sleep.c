/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_sleep.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/23 08:15:17 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/23 08:15:17 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	philo_sleep(t_philo *philo)
{
	philo->state = SLEEPING;
	if (!philo->config->a_philo_died && !philo->config->all_satiated)
		safe_write_msg(philo, IS_SLEEPING);
	if (usleep(philo->config->time_to_sleep * 1000) < 0)
		return (SYS_ERROR);
	if (philo->state == DEAD)
		return (0);
	return (1);
}
