/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_syntax_validation.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 15:22:18 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/15 18:30:12 by kkroon        ########   odam.nl         */
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

bool	is_redirection_token(t_token token)
{
	return ((token.type == REDIRECT_INPUT
			|| token.type == HEREDOC
			|| token.type == REDIRECT_OUTPUT
			|| token.type == REDIRECT_OUTPUT_APPEND));
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
		if (is_redirection_token(token)
			&& syntax_validations_redirections(data, i) == false)
			return (false);
		i++;
	}
	return (true);
}
