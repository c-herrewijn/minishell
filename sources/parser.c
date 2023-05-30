/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/23 16:01:57 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/05/30 17:52:09 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_count_arguments(t_data *data, size_t command_nr)
{
	size_t	i_token;
	int		argc;

	i_token = get_start_token(data, command_nr);
	argc = 0;
	while (i_token < data->nr_tokens && data->token_arr[i_token].type != PIPE)
	{
		if (is_redirection_token(data->token_arr[i_token]))
			i_token++;
		else
			argc++;
		i_token++;
	}
	return (argc);
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

// assumes command_nr <= nr tokens of type PIPE
size_t	get_start_token(t_data *data, size_t command_nr)
{
	size_t	token_nr;
	size_t	pipe_count;

	token_nr = 0;
	pipe_count = 0;
	while (command_nr > pipe_count)
	{
		if (data->token_arr[token_nr].type == PIPE)
			pipe_count++;
		token_nr++;
	}
	return (token_nr);
}

int	create_commands(t_data *data)
{
	size_t	i;

	data->nr_commands = get_nr_commands(data);
	if (data->nr_commands == 0)
		return (0);
	data->command_arr = ft_calloc(data->nr_commands, sizeof(t_command));
	if (data->command_arr == NULL)
		return (-1);
	i = 0;
	while (i < data->nr_commands)
	{
		if (create_command(data, i) < 0)
			return (-1);
		i++;
	}
	return (0);
}

int	parser(t_data *data)
{
	if (syntax_validation(data) == false)
	{
		write(STDERR_FILENO, "syntax error\n", 13);
		return (0);
	}
	else
	{
		if (create_commands(data) < 0)
			return (-1);
	}
	return (0);
}
