/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 15:06:52 by cherrewi      #+#    #+#                 */
/*   Updated: 2022/10/23 12:18:40 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Atoi = Array To Integer
Parses a string with digits to an int.
The first char can be a + or - sign.
Leading white spaces are skipped.
*/
int	ft_atoi(const char *str)
{
	long int	num;
	int			sign;

	num = 0;
	sign = 1;
	while (*str == ' ' || *str == '\f' || *str == '\n'
		|| *str == '\r' || *str == '\t' || *str == '\v')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit((int)(*str)))
		{
			break ;
		}
		num = num * 10;
		num = num + ((*str) - 48);
		str++;
	}
	return ((sign) * (num));
}
