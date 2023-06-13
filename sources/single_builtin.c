/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_builtin.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 17:12:43 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/13 17:42:05 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	single_export(t_node **head, t_data *data)
{
	int		export_format;
	char	**argv;

	argv = data->command_arr[0].argv;
	export_format = b_export_allowed_format(data->command_arr[0].argc, argv);
	if (argv[1][0] == '_' && (argv[1][1] == '\0' || argv[1][1] == '='
			|| argv[1][1] == '+'))
		return (0);
	if (export_format == 1)
	{
		if (b_export(data->command_arr[0].argc, argv, head) == -1)
			return (-1);
	}
	else if (export_format == 2)
	{
		if (b_export_concat(data->command_arr[0].argc, argv, head) == -1)
			return (-1);
	}
	else if (export_format == -1)
	{
		printf("incorrect format for export! >:(\n");
	}
	return (0);
}

int	execute_single_builtin(t_node **head, t_data *data)
{
	t_builtin	type;

	type = check_if_builtin(data->command_arr[0].argv[0]);
	if (type == B_ECHO)
		b_echo(data->command_arr[0].argc, data->command_arr[0].argv);
	if (type == B_CD)
		if (b_cd(data->command_arr[0].argc, data->command_arr[0].argv,
				head) < 0)
			return (-1);
	if (type == B_PWD)
		b_pwd();
	if (type == B_ENV)
		b_env(*head);
	if (type == B_EXIT)
		b_exit(data->command_arr[0].argv[1]);
	if (type == B_EXPORT)
		single_export(head, data);
	if (type == B_UNSET)
		b_unset(data->command_arr[0].argc, data->command_arr[0].argv, head);
	return (0);
}
