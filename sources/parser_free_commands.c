/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_free_commands.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 17:34:11 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/02 14:56:42 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_command_data(t_data *data, size_t command_nr)
{
	t_command		*command;
	size_t			i;

	command = &((data->command_arr)[command_nr]);
	i = 0;
	while (command->redirections[i] != NULL)
	{
		free (command->redirections[i]->word);
		free (command->redirections[i]);
		i++;
	}
	free (command->redirections);
	i = 0;
	while (command->argv[i] != NULL)
	{
		free (command->argv[i]);
		i++;
	}
	free (command->argv);
}

void	free_commands(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nr_commands)
	{
		free_command_data(data, i);
		i++;
	}
	free(data->command_arr);
	data->nr_commands = 0;
	data->command_arr = NULL;
}
