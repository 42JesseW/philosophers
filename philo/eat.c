/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/17 14:48:54 by jevan-de      #+#    #+#                 */
/*   Updated: 2023/01/18 10:10:36 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	set_death(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->table->lock);
	philo->table->__unsafe_someone_died = true;
	pthread_mutex_unlock(&philo->table->lock);
}

static void	unlock_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(&philo->forks[0]->lock);
	pthread_mutex_unlock(&philo->forks[1]->lock);
}

static int	single_fork_death(t_philosopher *philo)
{
	safe_write_msg(philo, TAKEN_FORK);
	if (usleep(philo->p_options.time_to_die_ms * 1000) == SYS_ERROR)
		return (0);
	return (1);
}

static void	set_if_saturated(t_philosopher *philo)
{
	bool		reached_saturation;
	t_options	*opts;

	opts = &philo->p_options;
	reached_saturation = (philo->p_eaten_amount == opts->must_eat_amount);
	if (!philo->is_saturated && reached_saturation)
	{
		pthread_mutex_lock(&philo->table->lock);
		philo->table->__unsafe_saturated_count++;
		pthread_mutex_unlock(&philo->table->lock);
		philo->is_saturated = true;
	}
}

int	start_eating(t_philosopher *philo)
{
	if (starved(philo, &philo->p_options))
		return (set_death(philo), 0);
	if (philo->p_options.philosopher_amount == 1)
		return (single_fork_death(philo));
	pthread_mutex_lock(&philo->forks[0]->lock);
	safe_write_msg(philo, TAKEN_FORK);
	pthread_mutex_lock(&philo->forks[1]->lock);
	safe_write_msg(philo, TAKEN_FORK);
	if (starved(philo, &philo->p_options))
		return (set_death(philo), unlock_forks(philo), 0);
	safe_write_msg(philo, IS_EATING);
	pthread_mutex_lock(&philo->table->lock);
	philo->__unsafe_p_last_eaten_time = get_time_ms();
	pthread_mutex_unlock(&philo->table->lock);
	if (!usleep_checked(philo, philo->p_options.time_to_eat_ms))
		return (unlock_forks(philo), 0);
	philo->p_eaten_amount++;
	if (philo->p_options.must_eat_amount != MISSING_OPTION)
		set_if_saturated(philo);
	unlock_forks(philo);
	return (1);
}
