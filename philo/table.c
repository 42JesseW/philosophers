/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   table.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/17 12:13:34 by jevan-de      #+#    #+#                 */
/*   Updated: 2023/01/17 18:19:41 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	destroy_fork_mutexes(t_fork *forks, int amount)
{
	int	idx;

	idx = 0;
	while (idx < amount)
	{
		pthread_mutex_destroy(&forks->lock);
		idx++;
	}
}

void	destroy_table(t_table *table)
{
	destroy_fork_mutexes(table->forks, table->fork_amount);
	pthread_mutex_destroy(&table->lock);
	free(table->forks);
}

static int	create_forks(t_table *table)
{
	int	amount;
	int	idx;

	amount = table->fork_amount;
	table->forks = (t_fork *)malloc(sizeof(t_fork) * amount);
	if (!table->forks)
		return (0);
	idx = 0;
	while (idx < amount)
	{
		if (pthread_mutex_init(&table->forks[idx].lock, NULL) == SYS_ERROR)
		{
			free(table->forks);
			return (0);
		}
		idx++;
	}
	return (1);
}

int	init_table(t_table *table, int fork_amount)
{
	table->fork_amount = fork_amount;
	if (!create_forks(table))
		return (0);
	table->__unsafe_allowed_to_write = true;
	table->__unsafe_saturated_count = 0;
	table->__unsafe_someone_died = false;
	table->__unsafe_all_saturated = false;
	if (pthread_mutex_init(&table->lock, NULL) == SYS_ERROR)
		return (0);
	return (1);
}
