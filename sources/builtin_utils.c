/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 15:53:59 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/07 20:36:35 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//s1 = argv[i]
//s2 = node->str
static bool		special_strcmp(char *s1, char *s2, int flag)
{
	//loop until equals and check if there is an equals sign after in str2
	//if at any point the characters in both strings arent equal, return -1
	//check if argv[0] == export , then i know it has an equals sign
	int i;
	int equals;
	
	i = 0;
	equals = (int)ft_strlen(s1);
	if (flag == 0)
		equals = index_of_c_in_str(s1, '=');
	while(s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return false;
		i++;
	}
	return false;
}

//can be called from PWD_update functions, unset and concat_export
int		is_in_env(int argc, char **argv, t_node **head)
{
	//argv[0] export or unset
	//argv[1] name=value
	//get argc and argv, split on '='
	//do strncmp for arr[0] strlen
	//get spot of equals
	t_node *node;
	int i;
	int flag;
	
	if (argc <= 1)
		return -1;
	node = *head;
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
	arr[0] = "test";
	arr[1] = str;
	arr[2] = NULL;
	return arr;
}