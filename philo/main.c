/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 09:44:44 by jevan-de      #+#    #+#                 */
/*   Updated: 2023/01/18 10:09:38 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	destroy_all(t_table *table, t_philosopher *philos)
{
	destroy_table(table);
	free(philos);
}

static int	wait_for_shutdown(t_watcher *watcher,
				t_philosopher *philos, int amount)
{
	int	exit_code;
	int	idx;

	idx = 0;
	exit_code = 1;
	while (idx < amount)
	{
		if (pthread_join(philos[idx].thread_id, NULL) == SYS_ERROR)
			exit_code = 0;
		idx++;
	}
	if (pthread_join(watcher->thread_id, NULL) == SYS_ERROR)
		exit_code = 0;
	return (exit_code);
}

int	main(int argc, char *argv[])
{
	t_options		opts;
	t_table			table;
	t_watcher		watcher;
	t_philosopher	*philos;

	if (!parse_options(argc, argv, &opts))
	{
		write(STDERR_FILENO, "Failed to parsed arguments.\n", 29);
		return (EXIT_FAILURE);
	}
	if (!init_table(&table, opts.philosopher_amount))
		return (EXIT_FAILURE);
	philos = init_philosophers(&opts, &table);
	if (!philos)
		return (destroy_table(&table), EXIT_FAILURE);
	init_watcher(&watcher, philos, &table, &opts);
	if (!start_philosophers(philos, opts.philosopher_amount))
		return (destroy_all(&table, philos), EXIT_FAILURE);
	if (!start_watcher(&watcher))
		return (destroy_all(&table, philos), EXIT_FAILURE);
	if (!wait_for_shutdown(&watcher, philos, opts.philosopher_amount))
		return (destroy_all(&table, philos), EXIT_FAILURE);
	return (destroy_all(&table, philos), EXIT_SUCCESS);
}
