/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 15:53:59 by kkroon        #+#    #+#                 */
/*   Updated: 2023/05/24 21:53:24 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_in_env(char *str, t_node **head)
{
	t_node *node;
	int i;
	int unset_len;
	int str_len;
	
	node = *head;
	i = 0;
	unset_len = ((int)ft_strlen("unset "));
	str_len = ((int)ft_strlen(str)) - unset_len;
	while(node != NULL)
	{
		if (ft_strncmp(str + unset_len, node->str, str_len) == 0)
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
