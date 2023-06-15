/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 15:03:09 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/15 18:09:43 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_for_child_processes(t_data *data)
{
	size_t	i;
	pid_t	return_pid;
	int		stat_loc;

	i = 0;
	while (i < data->nr_commands)
	{
		return_pid = waitpid(data->command_arr[i].pid, &stat_loc, 0);
		if (return_pid == -1)
		{
			perror(NULL);
			return (-1);
		}
		data->command_arr[i].exit_status = WEXITSTATUS(stat_loc);
		i++;
	}
	return (0);
}

void	run_child_process_and_exit(char **envp, t_data *data, size_t com_i)
{
	if (close_pipes_before_running_command_i(data, com_i) < 0)
		exit(1);
	if (apply_redirections(data, com_i) < 0)
		exit(1);
	if ((data->command_arr)[com_i].argc == 0)
		exit(0);
	if (check_if_builtin(data->command_arr[com_i].argv[0]) != NOT_BUILTIN)
		execute_command_builtin(&data->head, data, com_i);
	else if (data->paths != NULL)
		execute_command_from_path(envp,
			data->paths, &(data->command_arr)[com_i]);
	else
		execute_command_local_dir(envp,
			data->paths, &(data->command_arr)[com_i]);
}

int	execute_commands_loop(t_data *data, char **envp)
{
	size_t	i;
	pid_t	new_pid;

	i = 0;
	while (i < data->nr_commands)
	{
		new_pid = fork();
		if (new_pid == -1)
		{
			perror(NULL);
			return (free_envp_return(&envp, -1));
		}
		if (new_pid == 0)
		{
			run_child_process_and_exit(envp, data, i);
		}
		data->command_arr[i].pid = new_pid;
		i++;
	}
	return (0);
}

// contains functionality from "execute_commands_in_child_processes()"
// might need to free envp earlier if something returns -1
int	execute_commands(t_data *data)
{
	char	**envp;

	envp = NULL;
	if (create_envp_from_ll_env(&data->head, &envp) == -1)
		return (-1);
	if (data->nr_commands == 0)
		return (free_envp_return(&envp, 0));
	data->nr_pipes = data->nr_commands - 1;
	if (create_pipes(data) < 0)
		return (free_envp_return(&envp, -1));
	data->paths = get_path(envp);
	if (execute_commands_loop(data, envp) == -1)
		return (-1);
	if (close_all_pipes(data) < 0)
		return (free_envp_return(&envp, -1));
	if (wait_for_child_processes(data) < 0)
		return (free_envp_return(&envp, -1));
	return (free_envp_return(&envp, 0));
}
