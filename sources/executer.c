/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 15:03:09 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/15 15:07:46 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
void	exit_child_proc_with_error(t_command *command, char **paths, char ***envp)
{
	extern int	errno;

	free_double_char_pointer(*envp);
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

int execute_export(t_node **head, t_data *data, size_t i)
{
	int export_format;
	char **argv;
	int ret;
	
	ret = 0;
	argv = data->command_arr[i].argv;
	export_format = b_export_allowed_format(data->command_arr[i].argc, argv);
	if (argv[1][0] == '_' && (argv[1][1] == '\0' || argv[1][1] == '='  || argv[1][1] == '+'))
		return ret;
	if (export_format == 1)
		ret = b_export(data->command_arr[i].argc, argv, head);
	else if (export_format == 2)
		ret = b_export_concat(data->command_arr[i].argc, argv, head);
	else
	{
		ret = write(2, "export: `", 9);
		ret = write(2, argv[1], ft_strlen(argv[1]));
		ret = write(2, "': not a valid identifier\n", 26);
		if (ret == -1)
			return (-1);
		ret = 1;
	}
	return ret;
}

//how does it work with it being in a child process
//do i exit child process with error, what about malloc fail?
void execute_command_builtin(t_node **head, t_data *data, size_t i)
{
	t_builtin type;
	int ret;
	
	type = check_if_builtin(data->command_arr[i].argv[0]);
	if (type == B_ECHO)
		ret = b_echo(data->command_arr[i].argc, data->command_arr[i].argv);
	if (type == B_CD)
		ret = b_cd(data->command_arr[i].argc, data->command_arr[i].argv, head);
	if (type == B_PWD)
		ret = b_pwd();
	if (type == B_ENV)
		ret = b_env(*head);
	if (type == B_EXIT)
		ret = b_exit(data->command_arr[i].argv[1]);
	if (type == B_EXPORT)
		ret = execute_export(head, data, i);
	if (type == B_UNSET)
		ret = b_unset(data->command_arr[i].argc, data->command_arr[i].argv, head);
	exit(ret);
}

void	execute_command_local_dir(char **envp, char **paths,
	t_command *command)
{
	if (command->executable_location != NULL)
		free(command->executable_location);
	command->executable_location = ft_strdup(command->argv[0]);
	if (command->executable_location != NULL)
		execve(command->executable_location, command->argv, envp);
	exit_child_proc_with_error(command, paths, &envp);
}

void	execute_command_from_path(char **envp, char **paths,
	t_command *command)
{
	int	i;

	i = 0;
	command->executable_location = NULL;
	while (paths[i] != NULL)
	{
		if (command->executable_location != NULL)
			free(command->executable_location);
		command->executable_location
			= combine_command_path(paths[i], command->argv[0]);
		if (command->executable_location == NULL)
			exit_child_proc_with_error(command, paths, &envp);
		execve(command->executable_location, command->argv, envp);
		i++;
	}
	if (errno != EACCES)
	{
		execute_command_local_dir(envp, paths, command);
	}
	else
	{
		exit_child_proc_with_error(command, paths, &envp);
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
		execute_command_from_path(envp, data->paths, &(data->command_arr)[com_i]);
	else
		execute_command_local_dir(envp, data->paths, &(data->command_arr)[com_i]);
}

// stores path char ** in new memory
char	**get_path(char **envp)
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

//allocate listlen + 1 * sizeof(char *) to envp
//loop through ll env
//alloc envp[i] with ft_substr
int create_envp_from_ll_env(t_node **head, char ***envp)
{
	int listlen;
	t_node *node;
	int i;
	
	node = *head;
	listlen = list_len(*head);
	*envp = malloc((listlen + 1) * sizeof(char *));
	i = 0;
	if (*envp == NULL)
		return (-1);
	while (i < listlen)
	{
		(*envp)[i] = ft_substr(node->str, 0, ft_strlen(node->str));
		if ((*envp)[i] == NULL)
			return (free_envp_return(envp, -1));
		i++;
		node = node->next;
	}
	(*envp)[i] = NULL;
	return 0;
}

//helper function for freeing envp and returning
int free_envp_return(char ***envp, int n)
{
	free_double_char_pointer(*envp);
	return (n);
}

int execute_commands_loop(t_data *data, char **envp)
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

void	print_child_errors(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nr_commands)
	{
		if (data->command_arr[i].exit_status == 127)
		{
			if (data->paths != NULL)
				ft_printf_fd(STDERR_FILENO, "%s: command not found\n",
					data->command_arr[i].argv[0]);
		}
		i++;
	}
}
