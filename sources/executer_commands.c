/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer_commands.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 18:00:05 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/15 18:03:13 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		b_exit(data->command_arr[i].argv[1]);
	if (type == B_EXPORT)
		ret = execute_export(head, data, i);
	if (type == B_UNSET)
		ret = b_unset(data->command_arr[i].argc, data->command_arr[i].argv, head);
	if (ret != 0)
		exit (1);
	exit(0);
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
