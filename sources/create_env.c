#include "minishell.h"

void list_print(t_node *head)
{
	t_node *node;
	
	node = head;
	while(node != NULL)
	{
		printf("%s\n", node->str);
		node = node->next;
	}
}

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
