/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug_printing.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 22:28:28 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/13 16:21:59 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_first(t_node **head)
{
	//debug
	t_node *node = *head;
	if (*head == NULL)
	{
		printf("*head == NULL it seems\n");
		return ;
	}
	printf("node->str : %s\n", node->str);
}

void print_next(t_node **head)
{
	//debug
	t_node *node = *head;
	if (*head == NULL)
	{
		printf("*head == NULL it seems\n");
		return ;
	}
	int listlen = list_len(*head);
	if (listlen == 1)
	{
		printf("cant print, because list len is 1\n");
		return ;
	}
	printf("node->next->str : %s\n", node->next->str);
}

// for printing/debugging env
void list_print(t_node *head)
{
	t_node *node;
	
	node = head;
	if (head == NULL)
	{
		printf("head == NULL it seems\n");
		return ;
	}
	if (head->str == NULL)
	{
		printf("head->str == NULL it seems\n");
		return ;
	}
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

void print_2d_array(char **s)
{
	int i;

	i = 0;
	if (s[0] == NULL)
		printf("s[0] == NULL\n");
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

void	write_operator(t_token_type type)
{
	if (type == WORD)
		dprintf(2, "%s\n", "unexpected word");
	if (type == PIPE)
		dprintf(2, "|");
	if (type == REDIRECT_INPUT)
		dprintf(2, "<");
	if (type == HEREDOC)
		dprintf(2, "<<");
	if (type == REDIRECT_OUTPUT)
		dprintf(2, ">");
	if (type == REDIRECT_OUTPUT_APPEND)
		dprintf(2, ">>");
}

void	print_commands(t_data *data)
{
	size_t	i;
	size_t	i_r;
	size_t	i_argv;

	i = 0;
	while (i < data->nr_commands)
	{
		puts("argv:");
		i_argv = 0;
		while ((data->command_arr)[i].argv[i_argv] != NULL)
		{
			printf("%s\n", (data->command_arr)[i].argv[i_argv]);
			i_argv++;
		}
		puts("redirections:");
		i_r = 0;
		while ((data->command_arr)[i].redirections[i_r] != NULL)
		{
			write_operator((data->command_arr)[i].redirections[i_r]->redirection_type);
			dprintf(2, " %s\n", (data->command_arr)[i].redirections[i_r]->word);
			i_r++;
		}
		i++;
	}
}

//debug option to quickly check how env works when its completely empty
void	unset_all(t_node **head)
{
	int	i;
	int	len;

	i = 0;
	len = list_len(*head);
	while (i < len - 1)
	{
		list_remove_first(head);
		i++;
	}
}

void debug_env_etc(char *str, t_node **head, t_data *data)
{
	// for (int x = 0; x < data->nr_commands; x++)
	// 	for (int y = 0; data->command_arr[x].argv[y] != NULL; y++)
	// 		printf("argv[%d][%d] : %s\n", x, y, data->command_arr[x].argv[y]);

	if (ft_strncmp("$", str, 1) == 0)
		print_env_var(str, *head);
	if (ft_strncmp("unset all", str, 9) == 0)
		unset_all(head);
	if (ft_strncmp("remove first", str, 12) == 0)
		list_remove_first(head);
	if (ft_strncmp("remove on", str, 9) == 0)
	{
		int listlen;
	
		listlen = list_len(*head);
		// printf("listlen : %d\n", listlen);
		if (((int)ft_strlen(str)) < 11)
			return ;
		int n = str[10] - '0';
		// printf("n : %d\n", n);
		list_remove_index(head, n);
	}
	if (ft_strncmp("print first", str, 11) == 0)
		print_first(head);
	if (ft_strncmp("print next", str, 10) == 0)
		print_next(head);
	if (ft_strncmp("list len", str, 8) == 0)
		printf("list len : %d\n", list_len(*head));
}
