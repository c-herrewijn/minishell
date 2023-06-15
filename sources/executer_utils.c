/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 17:50:29 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/15 17:55:58 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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