/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 15:13:25 by cherrewi      #+#    #+#                 */
/*   Updated: 2022/10/19 15:13:26 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
finds needle in haysteck
len is part of the haysteck we take into account
*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (ft_strlen(needle) > ft_strlen(haystack))
		return (NULL);
	if (*needle == '\0')
		return ((char *)haystack);
	i = 0;
	while (ft_strlen(needle) + i <= len && *(haystack + i) != '\0')
	{
		if (ft_strncmp(haystack + i, needle, ft_strlen(needle)) == 0)
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
