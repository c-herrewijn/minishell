/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 15:53:59 by kkroon        #+#    #+#                 */
/*   Updated: 2023/05/24 21:33:59 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_in_env(char *str, t_node **head)
{
	t_node *node;
	int str_len;
	int i;

	node = *head;
	str_len = ((int)ft_strlen(str)) - ((int)ft_strlen("unset "));
	i = 0;
	while(node != NULL)
	{
		if (ft_strncmp(str + 6, node->str, str_len) == 0)
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
