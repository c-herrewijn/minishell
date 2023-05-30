/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_create_command.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 16:40:56 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/05/30 16:28:48 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_redirection(t_data *data, size_t command_nr, size_t *i_token)
{
	t_command		*command;
	t_redirection	*new_redirection;
	int				i_redirect;

	new_redirection = malloc(sizeof(t_redirection));
	if (new_redirection == NULL)
		return (-1);
	new_redirection->redirection_type = data->token_arr[*i_token].type;
	new_redirection->word = ft_strdup(data->token_arr[(*i_token) + 1].word);
	if (new_redirection->word == NULL)
		return (-1);
	i_redirect = 0;
	command = &((data->command_arr)[command_nr]);
	while ((command->redirections)[i_redirect] != NULL)
		i_redirect++;
	(command->redirections)[i_redirect] = new_redirection;
	(*i_token)++;
	return (0);
}

int	add_argv(t_data *data, size_t command_nr, size_t i_token)
{
	t_command	*command;
	int			i_argv;

	command = &((data->command_arr)[command_nr]);
	i_argv = 0;
	while (command->argv[i_argv] != NULL)
		i_argv++;
	command->argv[i_argv] = ft_strdup(data->token_arr[i_token].word);
	if (command->argv[i_argv] == NULL)
		return (-1);
	else
		return (0);
}

size_t	command_count_redirections(t_data *data, size_t command_nr)
{
	size_t	i_token;
	size_t	redirection_count;	

	redirection_count = 0;
	i_token = get_start_token(data, command_nr);
	while (i_token < data->nr_tokens && data->token_arr[i_token].type != PIPE)
	{
		if (is_redirection_token(data->token_arr[i_token]))
			redirection_count++;
		i_token++;
	}
	return (redirection_count);
}

int	malloc_redirection_and_argv_arrays(t_data *data, size_t command_nr)
{
	t_command	*command;
	size_t		redirection_count;

	command = &((data->command_arr)[command_nr]);
	command->argc = command_count_arguments(data, command_nr);
	command->argv = ft_calloc((command->argc + 1), sizeof(char *));
	if (command->argv == NULL)
		return (-1);
	redirection_count = command_count_redirections(data, command_nr);
	command->redirections
		= ft_calloc((redirection_count + 1), sizeof(t_redirection *));
	if (command->redirections == NULL)
		return (-1);
	return (0);
}

int	create_command(t_data *data, size_t command_nr)
{
	size_t		i_token;

	if (malloc_redirection_and_argv_arrays(data, command_nr) < 0)
		return (-1);
	i_token = get_start_token(data, command_nr);
	while (i_token < data->nr_tokens && data->token_arr[i_token].type != PIPE)
	{
		if (is_redirection_token(data->token_arr[i_token]))
		{
			if (add_redirection(data, command_nr, &i_token) < 0)
				return (-1);
		}
		else
		{
			if (add_argv(data, command_nr, i_token) < 0)
				return (-1);
		}
		i_token++;
	}
	return (0);
}
