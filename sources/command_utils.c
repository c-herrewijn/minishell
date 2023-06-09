/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 19:57:43 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/08 19:58:12 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	command_has_heredoc(t_data *data, size_t command_nr)
{
	t_command	*command;
	size_t		i;

	command = &((data->command_arr)[command_nr]);
	i = 0;
	while (command->redirections[i] != NULL)
	{
		if (command->redirections[i]->redirection_type == HEREDOC)
			return (true);
		i++;
	}
	return (false);
}
