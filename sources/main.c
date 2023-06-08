/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 12:36:57 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/08 15:19:54 by kkroon        ########   odam.nl         */
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
	free(data->pipes);
	data->pipes = NULL;
	free_tokens(data);
	free_commands(data);
}

static void	free_and_exit_with_perror(t_data *data, t_node **head)
{
	free_data(data);
	list_clear(head);
	perror(NULL);
	exit(1);
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
	data->nr_pipes = 0;
	data->pipes = NULL;
	data->paths = NULL;
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
		if (data.str == NULL) //if ctrl-D is send, this will also count
		{
			free_data(&data);
			write(STDOUT_FILENO, "exit\n", 5);
			exit(0);
		}
		add_history(data.str);
		
		if (lexer(&data) < 0)
			free_and_exit_with_perror(&data, &data.head);
		
		//debug
		// print_tokens(&data);
		
		if (parser(&data) < 0)
			free_and_exit_with_perror(&data, &data.head);

		// debug
		// print_commands(&data);
		debug_env_etc(data.str, &data.head, &data);

		if (execute_commands(&data) < 0)
			free_and_exit_with_perror(&data, &data.head);

		// debug
		// printf("%s\n", data.str);

		if (old_builtin_test(data.str, &data.head, &data) < 0)
			free_and_exit_with_perror(&data, &data.head);

		free_data(&data);
	}
	return (0);
}
