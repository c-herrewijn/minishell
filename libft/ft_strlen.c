/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 15:13:03 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/05/11 13:37:47 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	c;

	if (s == NULL)
		return (0);
	c = 0;
	while (*s)
	{
		s++;
		c++;
	}
	return (c);
}
