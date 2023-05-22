/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_unset.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 16:50:05 by kkroon        #+#    #+#                 */
/*   Updated: 2023/05/22 15:40:04 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pop off first
// saves the original pointer
void list_remove_first(t_node **head)
{
	t_node *node;

	node = *head;
	*head = (*head)->next;
	free(node);
}

// might be a workaround to not use temp, not sure yet
void list_remove_index(t_node **head, int spot)
{
	int i;
	t_node *node;
	t_node *temp;

	i = 0;
	node = *head;
	temp = NULL;
	if (spot == 0)
		list_remove_first(head);
	while(i < (spot - 1))
	{
		node = node->next;
		i++;
	}
	temp = node->next;
	node->next = temp->next;
	free(temp);
}

// might need to do something with magic numbers
void	b_unset(char *str, t_node **head)
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
				list_remove_index(head, i);
			return ;
		}
		i++;
		node = node->next;
	}
}
