/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/17 12:14:35 by jevan-de      #+#    #+#                 */
/*   Updated: 2023/01/18 12:12:54 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	done(t_philosopher *philo)
{
	bool	is_done;

	pthread_mutex_lock(&philo->table->lock);
	is_done = (
			philo->table->__unsafe_someone_died
			|| philo->table->__unsafe_all_saturated
			);
	pthread_mutex_unlock(&philo->table->lock);
	return (is_done);
}

/*
** First time `p_last_eaten_time` is set, it does not need
** to be protected since the philosophers all start before
** the monitoring thread starts.
*/
void	*philosophize(void *_philo)
{
	t_philosopher	*philo;

	philo = _philo;
	pthread_mutex_lock(&philo->table->lock);
	pthread_mutex_unlock(&philo->table->lock);
	if (philo->p_number % 2 == 0)
		usleep_checked(philo, (philo->p_options.time_to_eat_ms / 2));
	while (true)
	{
		usleep(100);
		if (!start_eating(philo))
			break ;
		if (done(philo))
			break ;
		if (!start_sleeping(philo))
			break ;
		if (done(philo))
			break ;
		safe_write_msg(philo, IS_THINKING);
	}
	return (NULL);
}

int	start_philosophers(t_philosopher *philos, int amount)
{
	int	idx;
	int	ret;

	idx = 0;
	while (idx < amount)
	{
		ret = pthread_create(
				&philos[idx].thread_id,
				NULL,
				philosophize,
				&philos[idx]
				);
		if (ret == SYS_ERROR)
			return (0);
		idx++;
	}
	return (1);
}

static void	set_forks(t_philosopher *philo)
{
	int	idx[2];

	idx[0] = philo->p_number - 2;
	if (philo->p_number == 1)
		idx[0] = philo->p_options.philosopher_amount - 1;
	idx[1] = philo->p_number - 1;
	if ((philo->p_number % 2) == 1)
	{
		philo->forks[0] = &philo->table->forks[idx[0]];
		philo->forks[1] = &philo->table->forks[idx[1]];
	}
	else
	{
		philo->forks[0] = &philo->table->forks[idx[1]];
		philo->forks[1] = &philo->table->forks[idx[0]];
	}
}

t_philosopher	*init_philosophers(t_options *options, t_table *table)
{
	t_philosopher	*philos;
	int				idx;

	philos = malloc(sizeof(t_philosopher) * options->philosopher_amount);
	if (!philos)
		return (NULL);
	idx = 0;
	while (idx < options->philosopher_amount)
	{
		philos[idx].p_number = idx + 1;
		philos[idx].__unsafe_p_last_eaten_time = get_time_ms();
		philos[idx].p_options = *options;
		philos[idx].p_eaten_amount = 0;
		philos[idx].table = table;
		philos[idx].is_saturated = false;
		set_forks(&philos[idx]);
		idx++;
	}
	return (philos);
}
