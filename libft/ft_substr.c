/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 15:13:47 by cherrewi      #+#    #+#                 */
/*   Updated: 2022/11/12 21:25:23 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
copies a substring to new memory
starting at position 'start' not more than 'len' chars
copies not more chars than present in the string
one extra byte is allocated for the new string, so it is null terminated
note: 'start' is a zero-based index!
if malloc fails, NULL is returned
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*new_str;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		new_str = malloc(1 * sizeof(char));
	else if (ft_strlen(s) - start > len)
		new_str = malloc(len + 1 * sizeof(char));
	else
		new_str = malloc((ft_strlen(s) - start + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s) - start && i < len && start < ft_strlen(s))
	{
		new_str[i] = s[i + start];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
