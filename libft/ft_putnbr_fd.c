/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 15:11:46 by cherrewi      #+#    #+#                 */
/*   Updated: 2022/10/21 12:47:42 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	num_to_write;

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			n = n * (-1);
			write(fd, "-", 1);
		}
		if (n < 10)
		{
			num_to_write = n + 48;
			write(fd, &num_to_write, 1);
		}
		else
		{
			ft_putnbr_fd(n / 10, fd);
			num_to_write = (n % 10) + 48;
			write(fd, &num_to_write, 1);
		}
	}
}
