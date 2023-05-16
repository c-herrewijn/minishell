/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 15:12:36 by cherrewi      #+#    #+#                 */
/*   Updated: 2022/10/23 13:55:54 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
stores the concatination of s1 and s2 in new memory
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	tot_len;

	if (!s1 || !s2)
		return (NULL);
	tot_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)ft_calloc(tot_len, sizeof(char));
	if (str == NULL)
		return (str);
	ft_strlcpy(str, s1, (tot_len * sizeof(char)));
	ft_strlcat(str, s2, (tot_len * sizeof(char)));
	return (str);
}
