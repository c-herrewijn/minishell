/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug_printing.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 22:28:28 by kkroon        #+#    #+#                 */
/*   Updated: 2023/05/19 22:29:48 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// for printing/debugging env
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

// probally will need some error checking
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

// kinda useless / not used
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
