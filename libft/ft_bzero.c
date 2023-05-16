/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 15:07:11 by cherrewi      #+#    #+#                 */
/*   Updated: 2022/10/19 15:25:08 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
writes n zeroed bytes to the string s
*/
void	ft_bzero(void *b, size_t n)
{
	while (n)
	{
		*(unsigned char *)b = 0;
		b++;
		n--;
	}
}
