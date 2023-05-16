/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 15:10:47 by cherrewi      #+#    #+#                 */
/*   Updated: 2022/10/19 15:10:48 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Returns the first occurrence of c (converted to an unsigned char) in string s.
Searches only hte first n bytes
*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)s == (unsigned char)c)
		{
			return ((void *)(s));
		}
		s++;
		i++;
	}
	return (NULL);
}
