/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_for_builtin.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 13:50:16 by kkroon        #+#    #+#                 */
/*   Updated: 2023/05/31 13:00:38 by kkroon        ########   odam.nl         */
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
			{
				if (str[i + 2] == '\0')
					return 3;
				return 2;
			}
		i++;
	}
	return 1;
}

// only works for basic input with only one command basicly
// need to use lexer/parser input later on
void	check_if_builtin(char *str, t_node **head)
{
	if (ft_strncmp("echo ", str, 5) == 0)
		b_echo(str);
	if (ft_strncmp("cd", str, 2) == 0)
		b_cd(str, head);
	if (ft_strncmp("pwd", str, 4) == 0)
		b_pwd();
	if (ft_strncmp("export ", str, 7) == 0)
	{
		int export_format;
		export_format = b_export_allowed_format(str);
		if (export_format == 1)
		{
			// printf("\nDEBUG : normal export\n");
			b_export(str, head);
		}
		else if (export_format == 2)
		{
			// printf("\nDEBUG : concat export\n");
			b_export_concat(str, head);
		}
		else if (export_format == -1)
			printf("incorrect format for export! >:(\n");
		else
			return ;
	}
	if (ft_strncmp("unset ", str, 6) == 0)
		b_unset(str, head, 1);
	if (ft_strncmp("env", str, 4) == 0)
		b_env(*head);
	if (ft_strncmp("exit", str, 4) == 0)
		b_exit(0);

	//for debugging
	if (ft_strncmp("$", str, 1) == 0)
		print_env_var(str, *head);
	if (ft_strncmp("unset all", str, 9) == 0)
		unset_all(head);
	if (ft_strncmp("remove first", str, 12) == 0)
		list_remove_first(head);
	if (ft_strncmp("remove on", str, 9) == 0)
	{
		int listlen;
	
		listlen = list_len(*head);
		// printf("listlen : %d\n", listlen);
		int n = str[10] - '0';
		// printf("n : %d\n", n);
		list_remove_index(head, n);
	}
	if (ft_strncmp("print first", str, 11) == 0)
		print_first(head);
	if (ft_strncmp("print next", str, 10) == 0)
		print_next(head);
	if (ft_strncmp("list len", str, 8) == 0)
		printf("list len : %d\n", list_len(*head));
	else
		return ;
}
