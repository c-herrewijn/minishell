/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 15:11:14 by cherrewi      #+#    #+#                 */
/*   Updated: 2022/10/19 15:11:15 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Copies n bytes from src to dest.
The move is also successful in case src and dest overlap
*/
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst == NULL && src == NULL)
		return (NULL);
	if (src > dst)
		ft_memcpy(dst, src, len);
	else
	{
		while (len)
		{
			*(unsigned char *)(dst + len - 1)
				= *(unsigned char *)(src + len - 1);
			len--;
		}
	}
	return (dst);
}
