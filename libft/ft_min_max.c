/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_min_max.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/27 22:48:40 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/05/01 23:42:34 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_max(size_t i, size_t j)
{
	if (i > j)
		return (i);
	else
		return (j);
}

size_t	ft_min(size_t i, size_t j)
{
	if (i < j)
		return (i);
	else
		return (j);
}
