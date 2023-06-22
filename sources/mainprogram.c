/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mainprogram.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/21 20:10:24 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/22 16:28:01 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// NOTE: if no command is executed (e.g. empty line), the exit status of the
//   previous command remains in memory
static void	store_final_exit_status(t_data *data)
{
	int	i_last;

	if (data->nr_commands >= 1)
	{
		i_last = data->nr_commands - 1;
		data->previous_exit_status = data->command_arr[i_last].exit_status;
	}
}

void	redirect_and_execute_single_builtin(t_data *data)
{
	int	terminal_out;
	int	terminal_in;

	terminal_in = dup(STDIN_FILENO);
	terminal_out = dup(STDOUT_FILENO);
	if (terminal_in < 0 || terminal_out < 0)
	{
		perror(NULL);
		return ;
	}
	if (apply_redirections_single_builtin(data) < 0)
	{
		perror(NULL);
		return ;
	}
	execute_single_builtin(&data->head, data);
	if (dup2(terminal_out, STDOUT_FILENO) < 0
		|| dup2(terminal_in, STDIN_FILENO) < 0)
		perror(NULL);
}

static void	exec_cmd(t_data *data)
{
	if (data->nr_commands == 1 && data->command_arr[0].argc > 0
		&& check_if_builtin(data->command_arr[0].argv[0]) != NOT_BUILTIN)
	{
		redirect_and_execute_single_builtin(data);
	}
	else
	{
		set_signals_blocked();
		if (execute_commands(data) < 0)
			free_and_exit_with_perror(data, &data->head);
	}
}

static void	lexer_parser_expander(t_data *data)
{	
	if (lexer(data) < 0)
		free_and_exit_with_perror(data, &data->head);
	if (parser(data) < 0)
		free_and_exit_with_perror(data, &data->head);
	if (expander(data) < 0)
		free_and_exit_with_perror(data, &data->head);
}

//prob want to somehow split this up into smaller chunks
void	main_loop(t_data data)
{
	while (true)
	{
		set_signals_parent();
		data.str = readline("minishell$ ");
		g_signumber = 0;
		if (signumber_check(&data) == 1)
			continue ;
		if (check_data_str(&data) == 1)
			continue ;
		add_history(data.str);
		lexer_parser_expander(&data);
		exec_cmd(&data);
		print_child_errors(&data);
		if (signumber_check(&data) == 1)
			continue ;
		store_final_exit_status(&data);
		free_data(&data);
	}
}
