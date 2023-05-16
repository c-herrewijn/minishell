/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 15:13:18 by cherrewi      #+#    #+#                 */
/*   Updated: 2022/10/19 15:13:19 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		result;

	i = 0;
	result = 0;
	while ((result == 0) && (i < n))
	{
		result = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (s1[i] == '\0' || s2[i] == '\0')
			break ;
		i++;
	}
	return (result);
}
