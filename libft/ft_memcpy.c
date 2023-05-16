/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 15:11:06 by cherrewi      #+#    #+#                 */
/*   Updated: 2022/10/19 15:11:07 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Copies n bytes from src to dest.
Src and dest should not overlap; there is no protection.
*/
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void		*p_dst_iter;

	if (dst == NULL && src == NULL)
		return (NULL);
	p_dst_iter = dst;
	while (n)
	{
		*(unsigned char *)p_dst_iter = *(unsigned char *)src;
		src++;
		p_dst_iter++;
		n--;
	}
	return (dst);
}
