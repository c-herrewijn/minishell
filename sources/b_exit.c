/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   b_exit.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 12:26:09 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/22 15:07:17 by kkroon        ########   odam.nl         */
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
void	b_exit(t_data *data, char *exit_status)
{
	int	n;

	n = 1;
	data->previous_exit_status = 0;
	if (exit_status == NULL)
		exit(data->previous_exit_status);
	if (ft_isinteger(exit_status) == false)
	{
		data->previous_exit_status = 255;
		write(2, "exit : ", 7);
		write(2, exit_status, ft_strlen(exit_status));
		write(2, ": numeric argument required\n", 28);
		exit(data->previous_exit_status);
	}
	n = ft_atoi(exit_status);
	data->previous_exit_status = n % 256;
	exit(data->previous_exit_status);
}
