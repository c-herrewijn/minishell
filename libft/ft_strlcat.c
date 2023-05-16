/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 15:12:46 by cherrewi      #+#    #+#                 */
/*   Updated: 2022/10/19 15:12:47 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Concatenates src and dst; always null terminates
Returns the sum of the original destination length and source length
*/
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	i;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	i = 0;
	while (i < src_len && i + dst_len + 1 < dstsize)
	{
		*(dst + dst_len + i) = *src;
		src++;
		i++;
	}
	*(dst + dst_len + i) = 0;
	if (dst_len < dstsize)
		return (src_len + dst_len);
	else
		return (src_len + dstsize);
}
