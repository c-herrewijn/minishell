/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_for_builtin.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 13:50:16 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/06 15:15:27 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get length of double char pointer
int		b_arr_len(char **s)
{
	int i;

	i = 0;
	while(s[i] != NULL)
	{
		i++;
	}
	return i;
}

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
int		b_export_allowed_format(char *str)
{
	int i;
	int flag;
	int equals;
	int elen;

	elen = (int)ft_strlen("export ");
	flag = 0;
	i = elen;
	equals = index_of_c_in_str(str, '=');
	if (ft_isdigit(str[i]) || equals == -1)
		return -1;
	while (str[i] != '\0' && i < equals)
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			if (!(str[i] == '+' && str[i + 1] == '=' && i > elen))
				return -1;
		if (i > elen)
			if (str[i] == '+' && str[i + 1] == '=')
				return 2;
		i++;
	}
	return 1;
}

// t_builtin	check_if_builtin(char *str)
int		check_if_builtin(char *str, t_node **head, t_data *data)
{
	int i;

	i = 0;
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
		i++;
	}
	if (ft_strncmp("export ", str, 7) == 0)
	{
		int export_format;
		export_format = b_export_allowed_format(str);
		if (export_format == 1)
		{
			// printf("\nDEBUG : normal export\n");
			if (b_export(str, head) == -1)
				return (-1);
		}
		else if (export_format == 2)
		{
			// printf("\nDEBUG : concat export\n");
			if (b_export_concat(str, head) == -1)
				return (-1);
		}
		else if (export_format == -1)
		{
			printf("incorrect format for export! >:(\n");
		}
		return 0;
	}
	if (ft_strncmp("unset ", str, 6) == 0)
		b_unset(str, head, 1);
	return 0;
}
