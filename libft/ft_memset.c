/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 15:11:22 by cherrewi      #+#    #+#                 */
/*   Updated: 2022/10/19 15:11:23 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Writes the memory with a fixed char.
Also useful to clean memory (fill with 0).
*/
void	*ft_memset(void *b, int c, size_t len)
{
	int		i;
	void	*p_iter;

	i = len;
	p_iter = b;
	while (i)
	{
		*(unsigned char *)p_iter = c;
		p_iter++;
		i--;
	}
	return (b);
}
