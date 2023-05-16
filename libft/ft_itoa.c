/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 15:08:27 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/02/09 14:29:55 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_nr_digits(size_t n)
{
	if (n < 10)
		return (1);
	else
		return (1 + get_nr_digits(n / 10));
}

static void	ft_store_itoa_abs(char *str, size_t abs_n)
{
	int	i;

	if (str)
	{
		i = get_nr_digits(abs_n) - 1;
		while (i >= 0)
		{
			str[i] = (abs_n % 10) + 48;
			abs_n = abs_n / 10;
			i--;
		}
	}
}

char	*ft_itoa(int n)
{
	char	*return_str;
	size_t	nr_digits;
	size_t	minus;
	size_t	abs_n;

	minus = 0;
	if (n < 0)
	{
		minus = 1;
		abs_n = (size_t)(-1 * (long int)n);
	}
	else
	{
		abs_n = n;
	}
	nr_digits = get_nr_digits(abs_n);
	return_str = ft_calloc(minus + nr_digits + 1, sizeof(char));
	if (return_str == NULL)
		return (return_str);
	if (minus)
	{
		*return_str = '-';
	}
	ft_store_itoa_abs(return_str + minus, abs_n);
	return (return_str);
}
