/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 12:36:57 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/10 11:30:17 by kkroon        ########   odam.nl         */
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

bool single_command_check(t_data data)
{
	int argc;
	char **argv;
	t_builtin type;
	
	argc = data.command_arr[0].argc;
	argv = data.command_arr[0].argv;
	type = check_if_builtin(argv[0]);
	if (argc > 0 && data.nr_commands == 1 && type != NOT_BUILTIN)
	{
		if (execute_single_builtin_command(&data.head, &data) < 0)
			free_and_exit_with_perror(&data, &data.head);
		return true;
	}
	else if (argc > 0 && data.nr_commands == 1 && type == NOT_BUILTIN)
	{
		printf("DEBUG: single non-builtin\n");
		if (execute_single_command(&data) < 0)
			free_and_exit_with_perror(&data, &data.head);
		return true;
	}
	return false;
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
		if (data.str[0] == '\0')
		{
			printf("DEBUG: data.str[0] == 0\n");
			free(data.str);
			continue;
		}
		// printf("\n\ndata.str : |%s|\n\n", data.str);
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
		// printf("DEBUG: argc %d : argv[0] : |%s|\n", data.command_arr[0].argc ,data.command_arr[0].argv[0]);
		if (single_command_check(data) == false)
		{
			if (execute_commands(&data) < 0)
			{
				printf("DEBUG: execute_commands() called\n");
				free_and_exit_with_perror(&data, &data.head);
			}
		}
		store_final_exit_status(&data);

		// debug
		// printf("%s\n", data.str);

		// if (old_builtin_test(&data.head, &data) < 0)
		// 	free_and_exit_with_perror(&data, &data.head);

		free_data(&data);
	}
	return (0);
}
