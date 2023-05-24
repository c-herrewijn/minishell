/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/23 16:01:57 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/05/24 21:53:27 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
pipes should be preceided and followed by a non-pipe token
https://www.man7.org/linux/man-pages/man1/bash.1.html#SHELL_GRAMMAR
*/
static bool	syntax_validation_pipe(t_data *data, size_t i_token)
{
	t_token			next_token;

	if (i_token == 0 || i_token == data->nr_tokens - 1)
		return (false);
	next_token = data->token_arr[i_token + 1];
	if (next_token.type == PIPE)
		return (false);
	return (true);
}

/*
redirections should be followed by a word
https://www.man7.org/linux/man-pages/man1/bash.1.html#REDIRECTION
*/
static bool	syntax_validations_redirections(t_data *data, size_t i_token)
{
	if (i_token == data->nr_tokens - 1)
		return (false);
	else
	{
		if (data->token_arr[i_token + 1].type != WORD)
			return (false);
	}
	return (true);
}

bool	syntax_validation(t_data *data)
{
	size_t	i;
	t_token	token;

	i = 0;
	while (i < data->nr_tokens)
	{
		token = data->token_arr[i];
		if ((token.type == PIPE) && syntax_validation_pipe(data, i) == false)
			return (false);
		if ((token.type == REDIRECT_INPUT
				|| token.type == HEREDOC
				|| token.type == REDIRECT_OUTPUT
				|| token.type == REDIRECT_OUTPUT_APPEND)
			&& syntax_validations_redirections(data, i) == false)
			return (false);
		i++;
	}
	return (true);
}

size_t	get_nr_commands(t_data *data)
{
	size_t	i;
	size_t	command_count;

	i = 0;
	command_count = 1;
	while (i < data->nr_tokens)
	{
		if (data->token_arr[i].type == PIPE)
			command_count++;
		i++;
	}
	return (command_count);
}

int	parser(t_data *data)
{
	data->nr_commands = get_nr_commands(data);
	
	// debug
	// printf("nr of commands = %zu\n", data->nr_commands);

	if (syntax_validation(data) == false)
	{
		write(STDERR_FILENO, "syntax error\n", 13);
		return (0);
	}
	else
	{
		// create command
		;
	}
	return (42);  // dummy return value
}
