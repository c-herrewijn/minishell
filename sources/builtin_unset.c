/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_unset.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 16:50:05 by kkroon        #+#    #+#                 */
/*   Updated: 2023/05/26 14:14:56 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void unset_all(t_node **head)
{
	int i;
	int len;

	i = 0;
	len = list_len(*head);
	while (i < len - 2)
	{
		// list_remove_first(head);
		list_remove_index(head, 1);
		i++;
	}
}

// pop off first
// saves the original pointer
void list_remove_first(t_node **head)
{
	t_node *node;

	if (*head == NULL)
	{
		printf("*head == NULL it seems\n");
		return ;
	}
	node = *head;
	*head = (*head)->next;
	free(node);
}

// might be a workaround to not use temp, not sure yet
void list_remove_index(t_node **head, int spot)
{
	int i;
	int listlen;
	t_node *node;
	t_node *temp;
	
	listlen = list_len(*head);
	if (*head == NULL || spot > listlen)
	{
		printf("*head == NULL || spot > listlen\n");
		return;
	}
	i = 0;
	node = *head;
	temp = NULL;
	if (spot == 0)
	{
		list_remove_first(head);
		return ;
	}
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
void	b_unset(char *str, t_node **head, int flag)
{
	int i;
	
	i = is_in_env(str, head, flag);
	if (i != -1)
		list_remove_index(head, i);
}
