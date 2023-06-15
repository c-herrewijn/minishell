/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   b_exit.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 12:26:09 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/15 15:53:57 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
maybe gotta think about errno and strerror/perror aswell

exit takes only one input, ignores the rest
the input given has to be a number between 0-255
1 : general errors
127 : command not found
255 : input not a number

if input is a number but in not range 0-255
then the exit code will be the input modulo 256
*/
void	b_exit(char *exit_status)
{
	int	n;

	n = 1;
	if (exit_status == NULL)
		exit(0);
	if (ft_isinteger(exit_status) == false)
	{
		write(2, "exit : ", 7);
		write(2, exit_status, ft_strlen(exit_status));
		write(2, ": numeric argument required\n", 28);
		exit(255);
	}
	n = ft_atoi(exit_status);
	if (n < 0 || n > 255)
	{
		n = n % 256;
		exit(n);
	}
	exit(0);
}
