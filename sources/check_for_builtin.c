/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_for_builtin.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 13:50:16 by kkroon        #+#    #+#                 */
/*   Updated: 2023/05/19 22:40:01 by kkroon        ########   odam.nl         */
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

// only works for basic input with only one command basicly
// need to use lexer/parser input later on
void	check_if_builtin(char *str, t_node **head)
{
	if (ft_strncmp("echo ", str, 5) == 0)
		b_echo(str);
	if (ft_strncmp("cd ", str, 3) == 0)
		b_cd(str, head);
	if (ft_strncmp("pwd", str, 4) == 0)
		b_pwd();
	if (ft_strncmp("export ", str, 7) == 0)
		b_export(str, head);
	if (ft_strncmp("unset ", str, 6) == 0)
		b_unset(str, head);
	if (ft_strncmp("env", str, 4) == 0)
		b_env(str, head);
	if (ft_strncmp("exit", str, 5) == 0)
		b_exit();
	if (ft_strncmp("$", str, 1) == 0)
		print_env_var(str, *head);
}
