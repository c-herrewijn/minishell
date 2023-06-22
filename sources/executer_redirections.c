/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer_redirections.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/05 19:52:01 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/22 12:15:18 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_fd_pipe_in(t_data *data, size_t i_command)
{
	if (dup2(data->pipes[i_command - 1][0], STDIN_FILENO) == -1)
	{
		perror(NULL);
		return (-1);
	}
	return (0);
}

static int	set_fd_pipe_out(t_data *data, size_t i_command)
{
	if (dup2(data->pipes[i_command][1], STDOUT_FILENO) == -1)
	{
		perror(NULL);
		return (-1);
	}
	return (0);
}

int	apply_redirections(t_data *data, size_t i_command)
{
	size_t	i_redirect;

	if (i_command != 0)
	{
		if (set_fd_pipe_in(data, i_command) < 0)
			return (-1);
	}
	if (i_command + 1 != data->nr_commands)
	{
		if (set_fd_pipe_out(data, i_command) < 0)
			return (-1);
	}
	i_redirect = 0;
	while (data->command_arr[i_command].redirections[i_redirect] != NULL)
	{
		if (apply_redirect(data, i_command, i_redirect) < 0)
			return (-1);
		i_redirect++;
	}
	return (0);
}
