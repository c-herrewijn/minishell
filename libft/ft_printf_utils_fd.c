/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_utils_fd.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/14 16:32:47 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/03/27 11:10:02 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	printf_putstr_fd(char *str, int *print_len, int fd)
{
	if (str)
	{
		ft_putstr_fd(str, fd);
		*print_len += ft_strlen(str);
	}
	else
		*print_len += write(fd, "(null)", 6);
}

void	printf_putnbr_fd(int nbr, int *print_len, int fd)
{
	char	c;

	if (nbr == -2147483648)
		*print_len += write(fd, "-2147483648", 11);
	else
	{
		if (nbr < 0)
		{
			nbr = nbr * (-1);
			*print_len += write(fd, "-", 1);
		}
		if (nbr < 10)
		{
			c = nbr + '0';
			*print_len += write(fd, &c, 1);
		}
		else
		{
			printf_putnbr_fd(nbr / 10, print_len, fd);
			printf_putnbr_fd(nbr % 10, print_len, fd);
		}
	}
}

void	printf_putunsnbr_fd(unsigned int nbr, int *print_len, int fd)
{
	char	c;

	if (nbr < 10)
	{
		c = nbr + '0';
		*print_len += write(fd, &c, 1);
	}
	else
	{
		printf_putunsnbr_fd(nbr / 10, print_len, fd);
		printf_putunsnbr_fd(nbr % 10, print_len, fd);
	}
}

void	printf_putunsignedhex_fd(unsigned long long nbr,
			int *print_len, char var_case, int fd)
{
	char	*base;

	base = NULL;
	if (var_case == 'l')
		base = "0123456789abcdef";
	else if (var_case == 'u')
		base = "0123456789ABCDEF";
	if (base)
	{
		if (nbr < 16)
			*print_len += write(fd, &base[nbr], 1);
		else
		{
			printf_putunsignedhex_fd(nbr / 16, print_len, var_case, fd);
			*print_len += write(fd, &base[nbr % 16], 1);
		}
	}
}
