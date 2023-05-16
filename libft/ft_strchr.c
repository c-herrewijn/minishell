/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 15:12:09 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/05/11 13:39:54 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Locates the first occurrence of c (converted to a char) in string s.
returns NULL if the character does not appear in the string
*/
char	*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	if ((char)c == 0)
	{
		while (*s)
			s++;
		return ((char *)s);
	}
	else
	{
		while (*s)
		{
			if (*s == (char)c)
				return ((char *)s);
			s++;
		}
	}
	return (NULL);
}
