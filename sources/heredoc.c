/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 17:11:48 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/20 21:28:17 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_heredoc_pipe(t_data *data, size_t command_nr)
{
	t_command	*command;

	command = &((data->command_arr)[command_nr]);
	if (pipe(command->heredoc_pipe) < 0)
		return (-1);
	return (0);
}

// returns the redirection index of the latest heredoc
// assumes there is at least 1 heredoc!
static size_t	get_latest_heredoc(t_command *command)
{
	size_t	i;
	size_t	latest_heredoc_index;

	i = 0;
	latest_heredoc_index = 0;
	while (command->redirections[i] != NULL)
	{
		if (command->redirections[i]->redirection_type == HEREDOC)
			latest_heredoc_index = i;
		i++;
	}
	return (latest_heredoc_index);
}

// return enumeration
// -1: something went wrong
// 0: heredoc stored succesfull
// 1: stop word
static int	heredoc_read_line(t_command *command, size_t i_redirect,
	char *stop_word, t_data *data)
{
	char	*here_str;

	if (write(STDOUT_FILENO, "> ", 2) < 0)
		return (-1);
	here_str = get_next_line(STDIN_FILENO);
	if (here_str == NULL)
		return (-1);
	if ((ft_strlen(here_str) - 1 == ft_strlen(stop_word)
			&& ft_strncmp(here_str, stop_word, ft_strlen(stop_word)) == 0))
	{
		free (here_str);
		return (1);
	}
	if (expand_here_str(&here_str, data->head, data) < 0)
		return (-1);
	if (i_redirect == get_latest_heredoc(command))
	{
		if (write(command->heredoc_pipe[1], here_str, ft_strlen(here_str)) < 0)
		{
			free (here_str);
			return (-1);
		}
	}
	free (here_str);
	return (0);
}

// assumes there is at least one heredoc, and its word is stored correctly
// NOTE: all heredocs are read, but only the last one is stored
static int	read_heredocs(t_command *command, t_data *data)
{
	char	*stop_word;
	size_t	i_redirect;
	int		res;

	i_redirect = 0;
	while (command->redirections[i_redirect] != NULL)
	{
		if (command->redirections[i_redirect]->redirection_type != HEREDOC)
		{
			i_redirect++;
			continue ;
		}
		stop_word = command->redirections[i_redirect]->word;
		res = 0;
		while (res == 0)
		{
			res = heredoc_read_line(command, i_redirect, stop_word, data);
			if (res < 0)
				return (-1);
		}
		i_redirect++;
	}
	if (close(command->heredoc_pipe[1]) < 0)
		return (-1);
	return (0);
}

int	add_heredoc(t_data *data, size_t command_nr)
{
	t_command	*command;

	command = &((data->command_arr)[command_nr]);
	if (command_has_heredoc(data, command_nr))
	{
		if (add_heredoc_pipe(data, command_nr) < 0)
			return (-1);
		if (read_heredocs(command, data) < 0)
			return (-1);
	}
	return (0);
}
