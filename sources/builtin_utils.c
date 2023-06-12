/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 15:53:59 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/12 17:04:28 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
s1 = argv[1]
s2 = node->str
loop until '=' sign in argv[1] if argv is export name=value
else loop through entire argv[1]
and at the end check if next character is a '='
*/
static bool	special_strcmp(char *s1, char *s2, int flag)
{
	int	i;
	int	equals;

	i = 0;
	equals = (int)ft_strlen(s1);
	if (flag == 0)
		equals = index_of_c_in_str(s1, '=');
	while (s2[i] != '\0' && i < equals)
	{
		if (s1[i] != s2[i])
			return (false);
		i++;
	}
	if (s2[i] == '=')
		return (true);
	return (false);
}

//called from PWD_update functions, unset, cd and concat_export
//in most cases argv[0] is prefix and argv[1] is str_to_find
int	index_in_env(char *prefix, char *str_to_find, t_node **head)
{
	t_node	*node;
	int		i;
	int		flag;

	if (str_to_find == NULL)
		return (-1);
	node = *head;
	if (node->str == NULL)
		return (-1);
	i = 0;
	flag = ft_strncmp("export\0", prefix, 7);
	while (node != NULL)
	{
		if (special_strcmp(str_to_find, node->str, flag) == true)
			return (i);
		i++;
		node = node->next;
	}
	return (-1);
}

void	free_double_char_pointer(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

// get length of double char pointer
int	b_arr_len(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
	{
		i++;
	}
	return (i);
}

/*
returns:
0 : no OLDPWD, no PWD
1 : yes OLDPWD, no PWD
2 : no OLDPWD, yes PWD
3 : yes OLDPWD, yes PWD
*/
int		pwd_in_env(t_node **head)
{
	int total;

	total = 0;
	if (index_in_env("test", "OLDPWD", head) >= 0)
		total += 1;
	if (index_in_env("test", "PWD", head) >= 0)
		total += 2;
	return total;
}
