/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 15:03:09 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/02 19:59:59 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_fd_pipe_in(t_data *data, size_t i_command)
{
	if (dup2(data->pipes[i_command - 1][0], STDIN_FILENO) == -1)
	{
		perror(NULL);
		return (-1);
	}
	return (0);
}

static int	set_fd_pipe_out(t_data *data, size_t i_command)
{
	if (dup2(data->pipes[i_command][1], STDOUT_FILENO) == -1)
	{
		perror(NULL);
		return (-1);
	}
	return (0);
}

int	set_filedescriptors(t_data *data, size_t i_command)
{
	if (i_command == 0)
	{
		;
		// if (set_fd_infile(data) < 0)
		// 	return (-1);
	}
	else
	{
		if (set_fd_pipe_in(data, i_command) < 0)
			return (-1);
	}
	if (i_command + 1 == data->nr_commands)
	{
		;
		// if (set_fd_outfile(data) < 0)
		// 	return (-1);
	}
	else
	{
		if (set_fd_pipe_out(data, i_command) < 0)
			return (-1);
	}
	return (0);
}


char	*combine_command_path(char *path, char *cmd)
{
	char	*command_path;
	size_t	malloc_len;

	malloc_len = ft_strlen(path) + ft_strlen("/") + ft_strlen(cmd) + 1;
	command_path = malloc(malloc_len * sizeof(char));
	if (command_path == NULL)
		return (NULL);
	ft_strlcpy(command_path, path, malloc_len);
	ft_strlcat(command_path, "/", malloc_len);
	ft_strlcat(command_path, cmd, malloc_len);
	return (command_path);
}

// exits child process with error
void	exit_child_proc_with_error(t_command *command, char **paths)
{
	extern int	errno;

	if (errno == EACCES)
	{
		perror(command->executable_location);
		exit(126);
	}
	if (errno == ENOENT)
	{
		if (paths == NULL)
			perror(command->argv[0]);
		exit(127);
	}
	perror(command->argv[0]);
	exit(1);
}

static void	execute_command_local_dir(char **envp, char **paths,
	t_command *command)
{
	if (command->executable_location != NULL)
		free(command->executable_location);
	command->executable_location = ft_strdup(command->argv[0]);
	if (command->executable_location != NULL)
		execve(command->executable_location, command->argv, envp);
	exit_child_proc_with_error(command, paths);
}

static void	execute_command_from_path(char **envp, char **paths,
	t_command *command)
{
	int	i;

	// dprintf(2, "execute command from path\n");
	i = 0;
	command->executable_location = NULL;
	while (paths[i] != NULL)
	{
		if (command->executable_location != NULL)
			free(command->executable_location);
		command->executable_location
			= combine_command_path(paths[i], command->argv[0]);
		if (command->executable_location == NULL)
			exit_child_proc_with_error(command, paths);
		
		// dprintf(2, "doing execve\n");
		// dprintf(2, "path: %s\n", command->executable_location);
		execve(command->executable_location, command->argv, envp);
		// dprintf(2, "execve failed path not found!\n");
		i++;
	}
	// dprintf(2, "WE ONLY GET HERE IF COMMAND DOES NOT EXIST!\n");
	if (errno != EACCES)
	{
		execute_command_local_dir(envp, paths, command);
	}
	else
	{
		exit_child_proc_with_error(command, paths);
	}
}

int	create_pipes(t_data *data)
{
	size_t	i;
	int		result;

	data->pipes = malloc(data->nr_pipes * 2 * sizeof(int));
	if (data->pipes == NULL)
		return (-1);
	i = 0;
	while (i < data->nr_pipes)
	{
		result = pipe(data->pipes[i]);
		if (result < 0)
		{
			free(data->pipes);
			data->pipes = NULL;
			return (-1);
		}
		i++;
	}
	return (0);
}

int	close_pipes_before_running_command_i(t_data *data, size_t i_command)
{
	size_t	i_pipe;

	i_pipe = 0;
	while (i_pipe < data->nr_pipes)
	{
		if (!(i_command == i_pipe + 1))
		{
			if (close(data->pipes[i_pipe][0]) < 0)
			{
				perror(NULL);
				return (-1);
			}
		}
		if (!(i_command == i_pipe))
		{
			if (close(data->pipes[i_pipe][1]) < 0)
			{
				perror(NULL);
				return (-1);
			}
		}
		i_pipe++;
	}
	return (1);
}


static void	run_child_process_and_exit(char **envp, t_data *data, size_t com_i)
{
	if (close_pipes_before_running_command_i(data, com_i) < 0)
		exit(1);
		
	// TODO;
	if (set_filedescriptors(data, com_i) < 0)  
		exit(1);
	if (data->paths != NULL)
		execute_command_from_path(envp, data->paths, &(data->command_arr)[com_i]);
	else
		execute_command_local_dir(envp, data->paths, &(data->command_arr)[com_i]);
}

// stores path char ** in new memory
static char	**get_path(char **envp)
{
	int	i;

	i = 0;
	if (envp == NULL)
		return (NULL);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

int	close_all_pipes(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nr_pipes)
	{
		if (close(data->pipes[i][0]) < 0)
		{
			perror(NULL);
			return (-1);
		}
		if (close(data->pipes[i][1]) < 0)
		{
			perror(NULL);
			return (-1);
		}
		i++;
	}
	return (1);
}

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

// contains functionality from "execute_commands_in_child_processes()"
int	execute_commands(t_data *data)
{
	// puts("executing commands!"); // debug

	pid_t	new_pid;
	size_t	i;
	extern char **environ;  // debug

	if (data->nr_commands == 0)
		return (0);
	data->nr_pipes = data->nr_commands - 1;
	if (create_pipes(data) < 0)
		return (-1);
	data->paths = get_path(environ);

	i = 0;
	while (i < data->nr_commands)  // only do this in case there are at least 2 commands, otherwise, run single command
	{
		// puts("before fork");
		new_pid = fork();
		// puts("after fork");
		if (new_pid == -1)
		{
			perror(NULL);
			return (-1);
		}
		if (new_pid == 0)
		{
			// puts("start running child process");
			run_child_process_and_exit(environ, data, i);
			// puts("SHOULD NOT SHOW");
		}
		data->command_arr[i].pid = new_pid;
		i++;
	}

	if (close_all_pipes(data) < 0)
		return (-1);

	if (wait_for_child_processes(data) < 0)
		return (-1);
	// puts("done with calling commands");

	return (0);
}
