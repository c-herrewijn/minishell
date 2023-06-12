/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_env.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 17:53:35 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/12 17:40:32 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//loop through ll env, returns len
int	list_len(t_node *head)
{
	t_node	*node;
	int		i;

	node = head;
	i = 0;
	if (head == NULL)
	{
		return (0);
	}
	while (node->next != NULL)
	{
		node = node->next;
		i++;
	}
	return (i + 1);
}

// need to keep track of both to not lose the pointer
void	list_clear(t_node **head)
{
	t_node	*cur_node;
	t_node	*next_node;

	cur_node = *head;
	next_node = *head;
	while (cur_node)
	{
		next_node = cur_node->next;
		if (cur_node->str != NULL)
			free(cur_node->str);
		free(cur_node);
		cur_node = next_node;
	}
}

// add to the end
// helper to list_create_env
// also used in b_export
// flag is just for debugging, need to remove later and update in minishell.h
int	list_append(t_node **head, char *str)
{
	t_node	*node;

	node = *head;
	while (node->next != NULL)
		node = node->next;
	node->next = malloc(sizeof(t_node));
	node->next->str = NULL;
	if (node->next == NULL)
		return (-1);
	node->next->str = str;
	node->next->next = NULL;
	return (0);
}

// main func, called from main
int	list_create_env(t_node **head, t_data data)
{
	int		i;
	char	*cpy;

	i = 1;
	if (b_arr_len(data.envp) == 0)
		return (0);
	cpy = ft_substr(data.envp[0], 0, ft_strlen(data.envp[0]));
	if (cpy == NULL)
		return (-1);
	*head = malloc(sizeof(t_node));
	if ((*head) == NULL)
	{
		free(cpy);
		return (-1);
	}
	(*head)->str = cpy;
	(*head)->next = NULL;
	while (data.envp[i] != NULL)
	{
		cpy = ft_substr(data.envp[i], 0, ft_strlen(data.envp[i]));
		if (list_append(head, cpy) == -1)
			return (-1);
		i++;
	}
	return (0);
}
