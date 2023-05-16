/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isinteger.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 13:34:47 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/04/21 13:35:06 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
check if string has format:
optionally starts with a plus '+' or minus '-' sign
only consists of digits [0-9]
is within range [INT_MIN, INT_MAX]
*/
bool	ft_isinteger(char *int_str)
{
	int			i;
	int			sign;
	long int	num;

	if (int_str == NULL || int_str[0] == '\0')
		return (false);
	i = 0;
	sign = 1;
	if (int_str[0] == '-')
		sign = -1;
	if (int_str[0] == '-' || int_str[0] == '+')
		i++;
	num = 0;
	while (int_str[i] != '\0')
	{
		if (ft_isdigit(int_str[i]) == false)
			return (false);
		num = num * 10;
		num = num + (int_str[i] - 48);
		i++;
	}
	num = num * sign;
	return (num >= INT_MIN && num <= INT_MAX);
}
