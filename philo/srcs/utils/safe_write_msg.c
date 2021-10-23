/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   safe_write_msg.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/22 15:11:11 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/22 15:11:11 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static char	*g_messages[] = {
	" has taken a fork\n",
	" is eating\n",
	" is sleeping\n",
	" is thinking\n",
	" died\n"
};

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

ssize_t	safe_write_msg_long(long timestamp)
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

ssize_t	safe_write_msg(t_philo *philo, enum e_msg type)
{
	long long	timestamp;
	char		*message;

	if (type != HAS_DIED)
		pthread_mutex_lock(&philo->config->write_lock);
	if (write(STDOUT_FILENO, "[", 1) < 0)
		return (-1);
	timestamp = get_time_ms() - philo->config->start_time;
	if (safe_write_msg_long(timestamp) < 0)
		return (-1);
	if (write(STDOUT_FILENO, "] ", 2) < 0)
		return (-1);
	if (safe_write_msg_long(philo->num) < 0)
		return (-1);
	message = g_messages[type];
	if (write(STDOUT_FILENO, message, ft_strlen(message)) < 0)
		return (-1);
	if (type != HAS_DIED)
		pthread_mutex_unlock(&philo->config->write_lock);
	return (1);
}
