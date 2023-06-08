/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_for_builtin.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 13:50:16 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/08 13:49:25 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int index_of_c_in_str(char *str, char c)
{
	int i;

	i = 0;
	if (str == NULL || c == 0)
		return -1;
	while(str[i] != '\0')
	{
		if (str[i] == c)
			return i;
		i++;
	}
	return -1;
}

/*
returns
-1 for invalid syntax
1 for normal name=value syntax
2 for concat name+=value syntax
*/
int		b_export_allowed_format(int argc, char **argv)
{
	int i;
	int equals;
	
	i = 0;
	equals = index_of_c_in_str(argv[1], '=');
	if (equals == -1)
		return -1;
	if (!(ft_isalnum(argv[1][i]) || argv[1][i] == '_'))
		return -1;
	while (argv[1][i] != '\0' && i < equals)
	{
		if (!(ft_isalnum(argv[1][i]) || argv[1][i] == '_'))
			if (!(argv[1][i] == '+' && argv[1][i + 1] == '=' && i > 0))
				return -1;
		if (i > 0)
			if (argv[1][i] == '+' && argv[1][i + 1] == '=')
				return 2;
		i++;
	}
	return 1;
}

t_builtin	check_if_builtin(char *str)
{
	if (ft_strncmp("echo\0", str, 5) == 0)
		return B_ECHO;
	if (ft_strncmp("cd\0", str, 3) == 0)
		return B_CD;
	if (ft_strncmp("pwd\0", str, 4) == 0)
		return B_PWD;
	if (ft_strncmp("EXPORT\0", str, 7) == 0)
		return B_EXPORT;
	if (ft_strncmp("UNSET\0", str, 6) == 0)
		return B_UNSET;
	if (ft_strncmp("env\0", str, 4) == 0)
		return B_ENV;
	if (ft_strncmp("exit\0", str, 5) == 0)
		return B_EXIT;
	else
		return NOT_BUILTIN;
}

int		old_builtin_test(char *str, t_node **head, t_data *data)
{
	int i;

	i = 0;
	if (data->nr_commands == 0)
		return 0;
	while(i < data->nr_commands)
	{
		if (ft_strncmp("echo\0", data->command_arr[i].argv[0], 5) == 0)
			b_echo(data->command_arr[i].argc, data->command_arr[i].argv);
		if (ft_strncmp("cd\0", data->command_arr[i].argv[0], 3) == 0)
			if (b_cd(data->command_arr[i].argc, data->command_arr[i].argv, head) < 0)
				return -1;
		if (ft_strncmp("pwd\0", data->command_arr[i].argv[0], 4) == 0)
			b_pwd();
		if (ft_strncmp("env\0", data->command_arr[i].argv[0], 4) == 0)
			b_env(*head);
		if (ft_strncmp("exit\0", data->command_arr[i].argv[0], 5) == 0)
			b_exit(data->command_arr[i].argv[1]);
		if (ft_strncmp("export\0", data->command_arr[i].argv[0], 7) == 0)
		{
			int export_format;
			export_format = b_export_allowed_format(data->command_arr[i].argc, data->command_arr[i].argv);
			if (export_format == 1)
			{
				printf("\nDEBUG : normal export\n");
				if (b_export(data->command_arr[i].argc, data->command_arr[i].argv, head) == -1)
					return (-1);
			}
			else if (export_format == 2)
			{
				printf("\nDEBUG : concat export\n");
				if (b_export_concat(data->command_arr[i].argc, data->command_arr[i].argv, head) == -1)
					return (-1);
			}
			else if (export_format == -1)
			{
				printf("incorrect format for export! >:(\n");
			}
			return 0;
		}
		if (ft_strncmp("unset\0", data->command_arr[i].argv[0], 6) == 0)
			b_unset(data->command_arr[i].argc, data->command_arr[i].argv, head);
		i++;
	}
	return 0;
}
