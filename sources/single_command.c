/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_command.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 17:12:45 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/09 19:14:06 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//will use functions from the executer
//basicly executer without pipes
int execute_single_command(t_data *data)
{
	extern char **environ;
	pid_t	new_pid;
	
	data->paths = get_path(environ);
	new_pid = fork();
	if (new_pid == -1)
	{
		perror(NULL);
		return (-1);
	}
	if (new_pid == 0)
	{
		if (apply_redirections(data, 0) < 0)  
			exit(1);
		if ((data->command_arr)[0].argc == 0)
			exit(0);
		if (data->paths != NULL)
			execute_command_from_path(environ, data->paths, &(data->command_arr)[0]);
		else
			execute_command_local_dir(environ, data->paths, &(data->command_arr)[0]);
	}
	data->command_arr[0].pid = new_pid;
	if (wait_for_child_processes(data) < 0)
		return (-1);
	return 0;
}
