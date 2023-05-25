/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 12:36:57 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/05/25 21:15:31 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_leaks(void)
{
	// debug
	system("leaks minishell");
}

static void	free_data(t_data *data)
{
	free(data->str);
	data->str = NULL;
	free_tokens(data);
}

static void	free_and_exit(t_data *data, int exit_status)
{
	free_data(data);
	write(STDOUT_FILENO, "exit\n", 5);
	exit(exit_status);
}

static void	init_data_struct(t_data *data, int argc, char **argv, char **envp)
{
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->str = NULL;
	data->nr_tokens = 0;
	data->token_arr = NULL;
	data->nr_commands = 0;
	data->command_arr = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_node	*head;

	// might need to be t_node head
	// without the the pointer
	// and then update the other function that use the linked list

	// debug
	// atexit(check_leaks);  

	init_data_struct(&data, argc, argv, envp);
	list_create_env(&head, data);
	while (true)
	{
		data.str = readline("minishell$ ");
		if (data.str == NULL)
			free_and_exit(&data, 0);
		add_history(data.str);
		
		if (lexer(&data) < 0)
			free_and_exit(&data, 1);
		
		//debug
		// print_tokens(&data);
		
		if (parser(&data) < 0)
			free_and_exit(&data, 1);
		
		// debug
		// printf("%s\n", data.str);
		
		check_if_builtin(data.str, &head);

		
		free_data(&data);
	}
	return (0);
}
