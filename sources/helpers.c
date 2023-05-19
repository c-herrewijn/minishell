/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   helpers.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 16:50:05 by kkroon        #+#    #+#                 */
/*   Updated: 2023/05/19 19:34:26 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void list_remove_first(t_node **head)
{
	t_node *node;

	node = (*head)->next;
	free(*head);
	*head = node;
}

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

void print_env_var(char *str, t_node *head)
{
	t_node *node;
	int str_len;

	node = head;
	str_len = (int)ft_strlen(str);
	while(node != NULL)
	{
		if (ft_strncmp(str + 1, node->str, str_len - 1) == 0)
		{
			printf("%s\n", (node->str) + str_len);
			return ;
		}
		node = node->next;
	}
}

void print_2d_array(char **s)
{
	int i;

	i = 0;
	while(s[i] != NULL)
	{
		printf("%s\n", s[i]);
		i++;
	}
}
