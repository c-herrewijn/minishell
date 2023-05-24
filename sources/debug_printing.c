/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug_printing.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 22:28:28 by kkroon        #+#    #+#                 */
/*   Updated: 2023/05/24 18:15:16 by cherrewi      ########   odam.nl         */
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

void	print_tokens(t_data *data)
{
	int				i;
	t_token_type	type;

	i = 0;
	dprintf(2, "%zu tokens created:\n", data->nr_tokens);
	while (i < data->nr_tokens)
	{
		type = data->token_arr[i].type;
		if (type == WORD)
			dprintf(2, "%s\n", data->token_arr[i].word);
		if (type == PIPE)
			dprintf(2, "|\n");
		if (type == REDIRECT_INPUT)
			dprintf(2, "<\n");
		if (type == HEREDOC)
			dprintf(2, "<<\n");
		if (type == REDIRECT_OUTPUT)
			dprintf(2, ">\n");
		if (type == REDIRECT_OUTPUT_APPEND)
			dprintf(2, ">>\n");
		i++;
	}
}

char *tokens_to_string(t_data *data)
{
	size_t	i;
	size_t	len;
	t_token	token;
	char	*str;

	// malloc the correct length for the returnstring
	len = 1;  // start with space for final '\0'
	i = 0;
	while (i < data->nr_tokens)
	{
		token = data->token_arr[i];
		if (token.type == WORD)
			len += (ft_strlen(token.word) + 1);
		else if (token.type == PIPE || token.type == REDIRECT_INPUT || token.type == REDIRECT_OUTPUT)
			len += 2;
		else
			len += 3;
		i++;
	}
	str = ft_calloc(len, sizeof(char));
	
	// fill the returnstring: we strip final space by using len - 1
	i = 0;
	while (i < data->nr_tokens)
	{
		token = data->token_arr[i];
		if (token.type == WORD)
		{
			ft_strlcat(str, token.word, len - 1);
			ft_strlcat(str, " ", len - 1);
		}
		if (token.type == PIPE)
			ft_strlcat(str, "| ", len - 1);
		if (token.type == REDIRECT_INPUT)
			ft_strlcat(str, "< ", len - 1);
		if (token.type == REDIRECT_OUTPUT)
			ft_strlcat(str, "> ", len - 1);
		if (token.type == REDIRECT_OUTPUT_APPEND)
			ft_strlcat(str, ">> ", len - 1);
		if (token.type == HEREDOC)
			ft_strlcat(str, "<< ", len - 1);
		i++;		
	}
	return (str);
}
