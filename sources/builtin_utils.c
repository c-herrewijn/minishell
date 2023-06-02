/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 15:53:59 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/02 19:21:27 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_in_env(char *str, t_node **head, int type)
{
	t_node *node;
	int i;
	int prefix;
	int str_len;
	
	node = *head;
	i = 0;
	if (type == 1)
		prefix = ((int)ft_strlen("unset "));
	else
		prefix = ((int)ft_strlen("export "));
	str_len = ((int)ft_strlen(str)) - prefix;
	while(node != NULL)
	{
		if (ft_strncmp(str + prefix, node->str, str_len) == 0)
		{
			if ((node->str)[str_len] == '=')
				return i;
		}
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
