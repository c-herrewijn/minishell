/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 15:13:31 by cherrewi      #+#    #+#                 */
/*   Updated: 2022/10/19 15:17:00 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
finds first char in string, searching right to left
*/
char	*ft_strrchr(const char *s, int c)
{
	const char	*str_i;

	str_i = s;
	while (*str_i)
	{
		str_i++;
	}
	while (str_i >= s)
	{
		if (*str_i == (char)c)
			return ((char *)str_i);
		str_i--;
	}
	return (NULL);
}
