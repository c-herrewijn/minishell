/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/23 16:01:57 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/05/25 15:23:18 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
