/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 15:12:20 by cherrewi      #+#    #+#                 */
/*   Updated: 2022/10/23 12:18:40 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Duplicates a string, and reseves memory via ft_calloc.
*/
char	*ft_strdup(const char *s1)
{
	size_t		len;
	size_t		i;
	const char	*s_iter;
	char		*s2;

	i = 0;
	len = 0;
	s_iter = s1;
	while (*s_iter)
	{
		len++;
		s_iter++;
	}
	s2 = (char *)ft_calloc(len + 1, sizeof(char));
	if (s2 == NULL)
		return (s2);
	while (i < len)
	{
		*(s2 + i) = *(s1 + i);
		i++;
	}
	return (s2);
}
