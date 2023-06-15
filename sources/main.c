/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 12:36:57 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/15 17:04:05 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_leaks(void)
{
	// debug
	system("leaks minishell");
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

		// if (expander(&data) < 0)
		// 	free_and_exit_with_perror(&data, &data.head);

		// debug
		// print_commands(&data);
		debug_env_etc(data.str, &data.head, &data);

		if (data.nr_commands == 1 && data.command_arr[0].argc > 0 
				&& check_if_builtin(data.command_arr[0].argv[0]) != NOT_BUILTIN)
			execute_single_builtin(&data.head, &data);
		else if (execute_commands(&data) < 0)
			free_and_exit_with_perror(&data, &data.head);
		// printf("exit status: %d\n", data.previous_exit_status);
		store_final_exit_status(&data);
		free_data(&data);
	}
	return (0);
}
