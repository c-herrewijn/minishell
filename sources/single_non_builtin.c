/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_non_builtin.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 17:12:45 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/14 16:51:31 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void pid_zero(t_data *data, char **envp)
{
	if (apply_redirections(data, 0) < 0)
	{
		free_double_char_pointer(envp);
		exit(1);
	}
	if ((data->command_arr)[0].argc == 0)
	{
		free_double_char_pointer(envp);
		exit(0);
	}
	if (data->paths != NULL)
		execute_command_from_path(envp, data->paths, &(data->command_arr)[0]);
	else
		execute_command_local_dir(envp, data->paths, &(data->command_arr)[0]);
}

//will use functions from the executer
//basicly executer without pipes
int	execute_single_non_builtin(t_data *data)
{
	pid_t	new_pid;
	char	**envp;

	envp = NULL;
	if (create_envp_from_ll_env(&data->head, &envp) == -1)
		return (-1);
	data->paths = get_path(envp);
	new_pid = fork();
	if (new_pid == -1)
	{
		perror(NULL);
		return (free_envp_return(&envp, -1));
	}
	if (new_pid == 0)
		pid_zero(data, envp);
	data->command_arr[0].pid = new_pid;
	if (wait_for_child_processes(data) < 0)
		return (free_envp_return(&envp, -1));
	return (free_envp_return(&envp, 0));
}
