/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/11 20:46:19 by jevan-de      #+#    #+#                 */
/*   Updated: 2022/05/11 20:46:19 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}
