/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_abs.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/27 22:20:12 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/04/27 22:22:39 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_abs(int num)
{
	if (num >= 0)
		return (num);
	else
	{
		if (num == INT_MIN)
			return (num);
		else
			return (num * -1);
	}
}
