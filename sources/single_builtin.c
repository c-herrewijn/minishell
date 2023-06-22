/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_builtin.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 17:12:43 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/22 17:39:27 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_single_builtin(t_node **head, t_data *data)
{
	t_builtin	type;
	int			ret;

	type = check_if_builtin(data->command_arr[0].argv[0]);
	if (type == B_ECHO)
		ret = b_echo(data->command_arr[0].argc, data->command_arr[0].argv);
	if (type == B_CD)
		ret = b_cd(data->command_arr[0].argc, data->command_arr[0].argv, head);
	if (type == B_PWD)
		ret = b_pwd();
	if (type == B_ENV)
		ret = b_env(*head);
	if (type == B_EXIT)
		b_exit(data, data->command_arr[0].argv[1]);
	if (type == B_EXPORT)
		ret = execute_export(head, data, 0);
	if (type == B_UNSET)
		ret = b_unset(data->command_arr[0].argc,
				data->command_arr[0].argv, head);
	if (ret == 0)
		data->previous_exit_status = 0;
	if (ret != 0)
		data->command_arr[0].exit_status = 1;
	if (ret == -1)
		perror(NULL);
}
