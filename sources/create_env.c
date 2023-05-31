/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_env.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 17:53:35 by kkroon        #+#    #+#                 */
/*   Updated: 2023/05/31 17:53:37 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int list_len(t_node *head)
{
	t_node *node;
	int i;

	node = head;
	i = 0;
	if (head == NULL) //  || head->str == NULL (maybe need to add)
	{
		return 0;
	}
	while (node->next != NULL)
	{
		node = node->next;
		i++;
	}
	return i+1;
}

// need to keep track of both to not lose the pointer
void list_clear(t_node *head)
{
	t_node *cur_node;
	t_node *next_node;

	cur_node = head;
	next_node = head;
	while(cur_node)
	{
		next_node = cur_node->next;
		free(cur_node);
		cur_node = next_node;
	}
}

// add to the end
// helper to list_create_env
// also used in b_export
// flag is just for debugging, need to remove later and update in minishell.h
void list_append(t_node **head, char *str)
{
	t_node *node;

	node = *head;
	while(node->next != NULL)
		node = node->next;
	node->next = malloc(sizeof(t_node));
	node->next->str = str;
	node->next->next = NULL;
}

// main func, called from main
void list_create_env(t_node **head, t_data data)
{
	int i;
	char *cpy;
	int envplen;

	i = 1;
	envplen = b_arr_len(data.envp);
	if (envplen == 0)
		return ;
	cpy = ft_substr(data.envp[0], 0, ft_strlen(data.envp[0]));
	*head = malloc(sizeof(t_node));
	(*head)->str = cpy;
	(*head)->next = NULL;
	// if (envplen == 1)
	// 	return ;
	while(data.envp[i] != NULL)
	{
		cpy = ft_substr(data.envp[i], 0, ft_strlen(data.envp[i]));
		list_append(head, cpy);
		i++;
	}
}
