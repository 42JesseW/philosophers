/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   watcher.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/17 12:48:42 by jevan-de      #+#    #+#                 */
/*   Updated: 2023/01/18 09:58:43 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static bool	set_if_all_saturated(t_watcher *watcher)
{
	bool	done_watching;
	int		saturated_count;

	done_watching = false;
	pthread_mutex_lock(&watcher->table->lock);
	saturated_count = watcher->table->__unsafe_saturated_count;
	if (saturated_count == watcher->opts.philosopher_amount)
	{
		watcher->table->__unsafe_all_saturated = true;
		done_watching = true;
	}
	pthread_mutex_unlock(&watcher->table->lock);
	return (done_watching);
}

void	*watch(void *_watcher)
{
	t_watcher	*watcher;
	bool		done_watching;
	int			idx;

	watcher = _watcher;
	done_watching = false;
	while (!done_watching)
	{
		idx = 0;
		while (!done_watching && idx < watcher->opts.philosopher_amount)
		{
			if (starved(&watcher->philos[idx], &watcher->opts))
			{
				safe_write_msg(&watcher->philos[idx], HAS_DIED);
				pthread_mutex_lock(&watcher->table->lock);
				watcher->table->__unsafe_someone_died = true;
				pthread_mutex_unlock(&watcher->table->lock);
				done_watching = true;
			}
			idx++;
		}
		if (!done_watching && watcher->opts.must_eat_amount != MISSING_OPTION)
			done_watching = set_if_all_saturated(watcher);
	}
	return (NULL);
}

void	init_watcher(t_watcher *watcher, t_philosopher *philos,
					t_table *table, t_options *opts)
{
	watcher->philos = philos;
	watcher->table = table;
	watcher->opts = *opts;
}

int	start_watcher(t_watcher *watcher)
{
	return (!(pthread_create(&watcher->thread_id, NULL, watch, watcher) < 0));
}
