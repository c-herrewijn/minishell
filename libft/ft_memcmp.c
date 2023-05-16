/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 15:10:57 by cherrewi      #+#    #+#                 */
/*   Updated: 2022/10/23 12:18:40 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
The memcmp() function compares byte string s1 against byte string s2.
Both strings are assumed to be n bytes long.
*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	int		result;

	i = 0;
	result = 0;
	while ((result == 0) && (i < n))
	{
		result = *(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i);
		if (result)
			return (result);
		i++;
	}
	return (result);
}
