/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/17 12:52:19 by jevan-de      #+#    #+#                 */
/*   Updated: 2023/01/18 10:07:44 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static char	**get_messages(void)
{
	static char	*messages[] = {
		" has taken a fork\n",
		" is eating\n",
		" is sleeping\n",
		" is thinking\n",
		" died\n"
	};

	return (messages);
}

static char	*ft_strrev(char *s)
{
	unsigned int	i;
	size_t			j;
	char			temp;

	i = 0;
	j = ft_strlen((const char *)s) - 1;
	while (i < j)
	{
		temp = s[i];
		s[i] = s[j];
		s[j] = temp;
		i++;
		j--;
	}
	return (s);
}

static ssize_t	safe_write_msg_long(long timestamp)
{
	char	buff[MAX_LONG_LEN];
	long	remainder;
	int		idx;
	ssize_t	ret;

	ret = 0;
	remainder = timestamp;
	memset(buff, 0, MAX_LONG_LEN);
	if (timestamp == 0)
		return (write(STDOUT_FILENO, "0", 1));
	if (timestamp < 0)
	{
		ret = write(STDOUT_FILENO, "-", 1);
		remainder = -remainder;
	}
	idx = 0;
	while (ret != -1 && remainder > 0)
	{
		buff[idx] = (remainder % 10) + '0';
		remainder /= 10;
		idx++;
	}
	ft_strrev(buff);
	return (write(STDOUT_FILENO, buff, idx));
}

ssize_t	safe_write_msg(t_philosopher *philo, enum e_msg type)
{
	long long	timestamp;
	char		*message;

	pthread_mutex_lock(&philo->table->lock);
	if (philo->table->__unsafe_allowed_to_write)
	{
		if (type == HAS_DIED)
			philo->table->__unsafe_allowed_to_write = false;
		if (write(STDOUT_FILENO, "[", 1) < 0)
			return (-1);
		timestamp = get_time_ms() - philo->p_options.start_time;
		if (safe_write_msg_long(timestamp) < 0)
			return (-1);
		if (write(STDOUT_FILENO, "] ", 2) < 0)
			return (-1);
		if (safe_write_msg_long(philo->p_number) < 0)
			return (-1);
		message = get_messages()[type];
		if (write(STDOUT_FILENO, message, ft_strlen(message)) < 0)
			return (-1);
	}
	pthread_mutex_unlock(&philo->table->lock);
	return (1);
}
