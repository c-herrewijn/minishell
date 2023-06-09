/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_builtin.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 17:12:43 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/09 17:37:09 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_single_builtin_command(t_node **head, t_data *data)
{
	printf("DEBUG: IN execute_single_builtin_command()\n");
	t_builtin type;

	type = check_if_builtin(data->command_arr[0].argv[0]);
	if (type == B_ECHO)
		b_echo(data->command_arr[0].argc, data->command_arr[0].argv);
	if (type == B_CD)
		if (b_cd(data->command_arr[0].argc, data->command_arr[0].argv, head) < 0)
			return -1;
	if (type == B_PWD)
		b_pwd();
	if (type == B_ENV)
		b_env(*head);
	if (type == B_EXIT)
		b_exit(data->command_arr[0].argv[1]);
	if (type == B_EXPORT)
	{
		int export_format;
		export_format = b_export_allowed_format(data->command_arr[0].argc, data->command_arr[0].argv);
		if (export_format == 1)
		{
			printf("\nDEBUG : normal export\n");
			if (b_export(data->command_arr[0].argc, data->command_arr[0].argv, head) == -1)
				return -1;
		}
		else if (export_format == 2)
		{
			printf("\nDEBUG : concat export\n");
			if (b_export_concat(data->command_arr[0].argc, data->command_arr[0].argv, head) == -1)
				return -1;
		}
		else if (export_format == -1)
		{
			printf("incorrect format for export! >:(\n");
		}
	}
	if (type == B_UNSET)
		b_unset(data->command_arr[0].argc, data->command_arr[0].argv, head);
	return 0;
}
