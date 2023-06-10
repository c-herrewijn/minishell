/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 15:53:59 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/10 15:01:06 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//s1 = argv[1]
//s2 = node->str
//loop until '=' sign in argv[1] if argv is export name=value
//else loop through entire argv[1] and at the end check if next character is a '='
static bool		special_strcmp(char *s1, char *s2, int flag)
{
	int i;
	int equals;
	
	i = 0;
	equals = (int)ft_strlen(s1);
	if (flag == 0)
		equals = index_of_c_in_str(s1, '=');	
	while(s2[i] != '\0' && i < equals)
	{
		if (s1[i] != s2[i])
			return false;
		i++;
	}
	if (s2[i] == '=')
		return true;
	return false;
}

//can be called from PWD_update functions, unset, cd and concat_export

//need to change to location_env(char **prefix, char **str_to_find, t_node **head)
int		is_in_env(int argc, char **argv, t_node **head)
{
	t_node *node;
	int i;
	int flag;
	
	if (argc <= 1)
		return -1;
	node = *head;
	if (node->str == NULL)
		return -1;
	i = 0;
	flag = ft_strncmp("export\0", argv[0], 7);
	while(node != NULL)
	{
		if (special_strcmp(argv[1], node->str, flag) == true)
			return i;
		i++;
		node = node->next;
	}
	return -1;
}

void	free_double_char_pointer(char **s)
{
	int i;
	
	i = 0;
	while(s[i] != NULL)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

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

char **make_is_in_env_compatible(char *str)
{
	char **arr;

	arr = malloc(3 * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	arr[0] = "test";
	arr[1] = str;
	arr[2] = NULL;
	return arr;
}