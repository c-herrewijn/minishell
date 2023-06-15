/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 13:52:14 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/15 14:42:52 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data(t_data *data)
{
	free(data->str);
	data->str = NULL;
	free(data->pipes);
	data->pipes = NULL;
	free_tokens(data);
	free_commands(data);
}

void	free_and_exit_with_perror(t_data *data, t_node **head)
{
	free_data(data);
	//rl_clear_history here i think
	list_clear(head);
	perror(NULL);
	exit(1);
}

void	init_data_struct(t_data *data, int argc, char **argv, char **envp)
{
	data->argc = argc;
	data->argv = argv;
	data->command_arr = NULL;
	data->envp = envp;
	data->head = NULL;
	data->nr_commands = 0;
	data->nr_pipes = 0;
	data->nr_tokens = 0;
	data->paths = NULL;
	data->pipes = NULL;
	data->previous_exit_status = 0;
	data->str = NULL;
	data->token_arr = NULL;
}

int	check_data_str(t_data *data)
{
	// printf("\n\ndata.str : |%s|\n\n", data.str);
	if (data->str == NULL) //if ctrl-D is send, this will also count
	{
		free_data(data);
		write(STDOUT_FILENO, "exit\n", 5);
		exit(0);
	}
	if (data->str[0] == '\0')
	{
		free(data->str);
		return (1);
	}
	return (0);
}
