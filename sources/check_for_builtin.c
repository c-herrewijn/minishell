/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_for_builtin.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 13:50:16 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/15 16:48:52 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	index_of_c_in_str(char *str, char c)
{
	int	i;

	i = 0;
	if (str == NULL || c == 0)
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

/*
returns
-1 for invalid syntax
1 for normal name=value syntax
2 for concat name+=value syntax
*/
int	b_export_allowed_format(int argc, char **argv)
{
	int	i;
	int	equals;

	i = 0;
	equals = index_of_c_in_str(argv[1], '=');
	if (equals == -1)
		return (-1);
	if (!(ft_isalnum(argv[1][i]) || argv[1][i] == '_'))
		return (-1);
	while (argv[1][i] != '\0' && i < equals)
	{
		if (!(ft_isalnum(argv[1][i]) || argv[1][i] == '_'))
			if (!(argv[1][i] == '+' && argv[1][i + 1] == '=' && i > 0))
				return (-1);
		if (i > 0)
			if (argv[1][i] == '+' && argv[1][i + 1] == '=')
				return (2);
		i++;
	}
	return (1);
}

t_builtin	check_if_builtin(char *str)
{
	if (ft_strncmp("echo\0", str, 5) == 0)
		return (B_ECHO);
	if (ft_strncmp("cd\0", str, 3) == 0)
		return (B_CD);
	if (ft_strncmp("pwd\0", str, 4) == 0)
		return (B_PWD);
	if (ft_strncmp("export\0", str, 7) == 0)
		return (B_EXPORT);
	if (ft_strncmp("unset\0", str, 6) == 0)
		return (B_UNSET);
	if (ft_strncmp("env\0", str, 4) == 0)
		return (B_ENV);
	if (ft_strncmp("exit\0", str, 5) == 0)
		return (B_EXIT);
	else
		return (NOT_BUILTIN);
}
