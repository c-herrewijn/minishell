/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer_apply_redirect.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 12:14:15 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/22 12:25:15 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// supported redirection types: REDIRECT_OUTPUT and REDIRECT_OUTPUT_APPEND
static int	redirect_output(t_data *data, size_t i_command, size_t i_redirect)
{
	t_redirection	*redirection;
	int				fd;

	redirection = data->command_arr[i_command].redirections[i_redirect];
	if (redirection->redirection_type == REDIRECT_OUTPUT)
		fd = open(redirection->word, O_TRUNC | O_CREAT | O_WRONLY, 0644);
	else
		fd = open(redirection->word, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd == -1)
	{
		perror(redirection->word);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror(NULL);
		return (-1);
	}
	return (0);
}

static int	redirect_input(t_data *data, size_t i_command, size_t i_redirect)
{
	t_redirection	*redirection;
	int				fd;

	redirection = data->command_arr[i_command].redirections[i_redirect];
	fd = open(redirection->word, O_RDONLY);
	if (fd == -1)
	{
		perror(redirection->word);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror(NULL);
		return (-1);
	}
	return (0);
}

// redirect inputs and outputs, but not heredoc
int	apply_redirect(t_data *data, size_t i_command, size_t i_redirect)
{
	t_redirection	*redirection;

	redirection = data->command_arr[i_command].redirections[i_redirect];
	if (redirection->redirection_type == REDIRECT_OUTPUT
		|| redirection->redirection_type == REDIRECT_OUTPUT_APPEND)
	{
		if (redirect_output(data, i_command, i_redirect) < 0)
			return (-1);
	}
	if (redirection->redirection_type == REDIRECT_INPUT)
	{
		if (redirect_input(data, i_command, i_redirect) < 0)
			return (-1);
	}
	if (redirection->redirection_type == HEREDOC)
	{
		if (dup2(data->command_arr[i_command].heredoc_pipe[0],
				STDIN_FILENO) == -1)
		{
			perror(NULL);
			return (-1);
		}
	}
	return (0);
}
