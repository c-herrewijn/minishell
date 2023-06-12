/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extra_main.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/12 14:45:33 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/12 14:45:53 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void single_command_check(t_data data)
{
	t_builtin type;

	type = check_if_builtin(data.command_arr[0].argv[0]);
	if (type != NOT_BUILTIN)
	{
		if (execute_single_builtin_command(&data.head, &data) < 0)
			free_and_exit_with_perror(&data, &data.head);
	}
	if (type == NOT_BUILTIN)
	{
		printf("DEBUG: single non-builtin\n");
		if (execute_single_command(&data) < 0)
			free_and_exit_with_perror(&data, &data.head);
	}
}

int check_data_str(t_data *data)
{
	// printf("\n\ndata.str : |%s|\n\n", data.str);
	if (data->str == NULL) //if ctrl-D is send, this will also count
	{
		free_data(data);
		write(STDOUT_FILENO, "exit\n", 5);
		exit(0);
	}
	if (data->str[0] == '\0')
	{
		printf("DEBUG: data->str[0] == 0\n");
		free(data->str);
		return 1;
	}
	return 0;	
}
