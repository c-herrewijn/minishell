/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   b_unset.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 16:50:05 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/15 18:14:10 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pop off first
// saves the original pointer
void	list_remove_first(t_node **head)
{
	t_node	*node;
	int		listlen;

	if (*head == NULL)
		return ;
	listlen = list_len(*head);
	if (listlen == 1)
	{
		(*head)->str = NULL;
		return ;
	}
	node = *head;
	*head = (*head)->next;
	free(node);
}

static void	list_rm_i_helper(t_node **head, t_node *node, int spot)
{
	int		i;
	t_node	*temp;

	i = 0;
	temp = NULL;
	if (spot == 0)
	{
		list_remove_first(head);
		return ;
	}
	while (i < (spot - 1))
	{
		node = node->next;
		i++;
	}
	temp = node->next;
	node->next = temp->next;
	free(temp);
}

// might be a workaround to not use temp, not sure yet
int	list_remove_index(t_node **head, int spot)
{
	int		listlen;
	t_node	*node;

	listlen = list_len(*head);
	if (*head == NULL || spot > listlen)
		return (1);
	node = *head;
	if (listlen == 1)
	{
		if (node->str != NULL)
			free(node->str);
		node->str = NULL;
		node->next = NULL;
		return (0);
	}
	list_rm_i_helper(head, node, spot);
	return (0);
}

// argv[0] export or unset
// argv[1] name=value
int	b_unset(int argc, char **argv, t_node **head)
{
	int	i;

	if (argc <= 1)
		return (1);
	if (argv[1][0] == '_' && (argv[1][1] == '\0' || argv[1][1] == '='))
		return (1);
	if (*head == NULL)
		return (1);
	if ((*head)->str == NULL)
		return (1);
	i = index_in_env(argv[0], argv[1], head);
	if (i != -1)
		list_remove_index(head, i);
	return (0);
}
