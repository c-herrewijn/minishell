/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 12:36:57 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/20 13:25:57 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// debug
void	check_leaks(void)
{
	system("leaks minishell");
}

//prob want to somehow split this up into smaller chunks
void main_loop(t_data data)
{
	while (true)
	{
		data.str = readline("minishell$ ");
		signumber = 0;
		if (signumber_check(&data) == 1)
			continue;
		if (check_data_str(&data) == 1)
			continue;
		add_history(data.str);
		if (signumber_check(&data) == 1)
			continue;
		if (lexer(&data) < 0)
			free_and_exit_with_perror(&data, &data.head);
		if (signumber_check(&data) == 1)
			continue;
		if (parser(&data) < 0)
			free_and_exit_with_perror(&data, &data.head);
		if (signumber_check(&data) == 1)
			continue;
		if (expander(&data) < 0)
			free_and_exit_with_perror(&data, &data.head);
		debug_env_etc(data.str, &data.head, &data);
		if (data.nr_commands == 1 && data.command_arr[0].argc > 0 
				&& check_if_builtin(data.command_arr[0].argv[0]) != NOT_BUILTIN)
			execute_single_builtin(&data.head, &data);
		else if (execute_commands(&data) < 0)
			free_and_exit_with_perror(&data, &data.head);
		if (signumber_check(&data) == 1)
			continue;
		store_final_exit_status(&data);
		free_data(&data);
	}
}

// debug
// atexit(check_leaks);
// printf("data.str = %s\n", data.str);
// print_tokens(&data);
// print_commands(&data);
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	signumber = 0;
	init_data_struct(&data, argc, argv, envp);
	if (list_create_env(&data.head, data) < 0)
		free_and_exit_with_perror(&data, &data.head);
	if (update_shlvl(&data.head, data) < 0)
		free_and_exit_with_perror(&data, &data.head);
	
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	main_loop(data);
	return (0);
}
