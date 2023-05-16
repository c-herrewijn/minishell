/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 15:13:11 by cherrewi      #+#    #+#                 */
/*   Updated: 2022/10/23 13:24:19 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*new_str;

	if (!s || !f)
		return (0);
	new_str = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s))
	{
		new_str[i] = f(i, s[i]);
		i++;
	}
	return (new_str);
}
