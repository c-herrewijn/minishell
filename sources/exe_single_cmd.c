/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extra_main.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/12 14:45:33 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/15 14:42:55 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_single_command(t_data data)
{
	t_builtin	type;

	type = check_if_builtin(data.command_arr[0].argv[0]);
	if (type != NOT_BUILTIN)
	{
		if (execute_single_builtin(&data.head, &data) < 0)
			free_and_exit_with_perror(&data, &data.head);
	}
	if (type == NOT_BUILTIN)
	{
		if (execute_single_non_builtin(&data) < 0)
			free_and_exit_with_perror(&data, &data.head);
	}
}
