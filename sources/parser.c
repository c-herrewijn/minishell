/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/23 16:01:57 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/05/23 18:52:42 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Validations:
- redirections should be followed by a word
  https://www.man7.org/linux/man-pages/man1/bash.1.html#REDIRECTION
- pipes should be preceided and followed by a token
  https://www.man7.org/linux/man-pages/man1/bash.1.html#SHELL_GRAMMAR
*/
static bool	syntax_validation(t_data *data)
{
	// loop over the nr of commands commands
	// per command, select the relevant tokens (i.e between the pipes)

	// checks:
	// - nr of tokens should not be zero
	// - there should be a word after redirection token.

	return (true);  // dummy return
}


size_t	get_nr_commands(t_data *data)
{
	size_t 	i;
	size_t	command_count;

	i = 0;
	command_count = 1;
	while (i < data->nr_tokens)
	{
		if (data->token_arr[i].type == OPERATOR
			&& data->token_arr[i].operator[0] == '|')
		{
			command_count++;
		}
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
		// provide error
		;
	}
	else
	{
		// create command
		;
	}
	return (42);  // dummy return value
}
