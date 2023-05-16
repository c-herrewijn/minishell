/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 15:13:38 by cherrewi      #+#    #+#                 */
/*   Updated: 2022/10/23 13:08:16 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
creates a trimmed copy of s1 in new memory
chars are trimmed from front and back, not from the middle
*/
char	*ft_strtrim(char const *s1, char const *set)
{
	char const	*s_start;
	char const	*s_end;

	if (!s1)
		return (NULL);
	s_start = s1;
	s_end = s1 + ft_strlen(s1);
	if (!set)
		return (ft_strdup(s1));
	while (ft_strchr(set, (int)*s_start) != NULL && s_start < s_end)
		s_start++;
	while (ft_strchr(set, (int)*s_end) != NULL && s_start < s_end)
		s_end--;
	return (ft_substr(s_start, 0, (size_t)(s_end - s_start + 1)));
}
