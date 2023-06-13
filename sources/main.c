/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 12:36:57 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/13 17:43:50 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_leaks(void)
{
	// debug
	system("leaks minishell");
}

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

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	// debug
	// atexit(check_leaks);

	init_data_struct(&data, argc, argv, envp);
	if (list_create_env(&data.head, data) < 0)
		free_and_exit_with_perror(&data, &data.head);
	// list_print(data.head);
	while (true)
	{
		data.str = readline("minishell$ ");
		if (check_data_str(&data) == 1)
			continue;
		add_history(data.str);
		
		if (lexer(&data) < 0)
			free_and_exit_with_perror(&data, &data.head);
		
		//debug
		// print_tokens(&data);
		
		if (parser(&data) < 0)
			free_and_exit_with_perror(&data, &data.head);

		if (expander(&data) < 0)
			free_and_exit_with_perror(&data, &data.head);

		// debug
		// print_commands(&data);
		debug_env_etc(data.str, &data.head, &data);
		
		if (data.nr_commands == 1 && data.command_arr[0].argc > 0)
			execute_single_command(data);
		else if (execute_commands(&data) < 0)
			free_and_exit_with_perror(&data, &data.head);
		store_final_exit_status(&data);
		free_data(&data);
	}
	return (0);
}
