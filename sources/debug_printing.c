/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug_printing.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 22:28:28 by kkroon        #+#    #+#                 */
/*   Updated: 2023/05/22 20:22:23 by cherrewi      ########   odam.nl         */
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

void	print_tokens(t_token *token_arr, t_data *data)
{
	int	i;

	i = 0;
	dprintf(2, "%zu tokens created:\n", data->nr_tokens);
	while (i < data->nr_tokens)
	{
		if (token_arr[i].type == 'w')
			dprintf(2, "%s\n", token_arr[i].word);
		if (token_arr[i].type == 'o')
		{
			dprintf(2, "%c%c\n", token_arr[i].operator[0],
				token_arr[i].operator[1]);
		}
		i++;
	}
}
