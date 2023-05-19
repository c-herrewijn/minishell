#include "minishell.h"

/*
alot of these functions malloc inside
non of them accept malloced nodes as param
could change this later to use t_list ft_lst_funcs
but using them is kinda verbose,
however i am probally using them wrong
*/

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
void list_append(t_node **head, char *str)
{
	t_node *node;

	node = *head;
	while(node->next != NULL)
	{
		node = node->next;
	}
	node->next = malloc(sizeof(t_node));
	node->next->str = str;
	node->next->next = NULL;
}

// main func, called from main
void list_create_env(t_node **head, t_data data)
{
	int i;
	
	i = 1;
	*head = malloc(sizeof(t_node));
	(*head)->str = data.envp[0];
	(*head)->next = NULL;
	while(data.envp[i] != NULL)
	{
		list_append(head, data.envp[i]);
		i++;
	}
}
