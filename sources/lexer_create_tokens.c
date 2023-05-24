/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_create_tokens.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 15:31:40 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/05/24 15:19:08 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
calculates the length of word starting on position i
assumes i < strlen(str); and the char on pos i is not an unquoted blank or
operator char, so word_len >= 1
*/
static size_t	word_len(char *str, int i)
{
	size_t	word_len;

	word_len = 0;
	while (is_unquoted_blank(str, i) == false
		&& is_unquoted_operator_char(str, i) == false
		&& str[i] != '\0')
	{
		i++;
		word_len++;
	}
	return (word_len);
}

/*
assumes word_len >= 1
puts i to the index number of the last char of the word
*/
static int	create_word(char *str, t_token *token, size_t *i)
{
	size_t	len;

	len = word_len(str, *i);
	token->type = WORD;
	token->word = ft_substr(str, *i, len);
	if (token->word == NULL)
		return (-1);
	*i += (len - 1);
	return (0);
}

static void	create_operator(char *str, t_token *token, size_t *i)
{
	char c1;
	char c2;

	c1 = str[*i];
	c2 = str[(*i) + 1];
	token->word = NULL;
	if (c1 == '<' && c2 == '<')
		token->type = HEREDOC;
	else if (c1 == '>' && c2 == '>')
		token->type = REDIRECT_OUTPUT_APPEND;
	else if (c1 == '<')
		token->type = REDIRECT_INPUT;
	else if (c1 == '>')
		token->type = REDIRECT_OUTPUT;
	else if (c1 == '|')
		token->type = PIPE;
}

int	create_tokens(t_data *data)
{
	size_t	str_i;
	size_t	token_i;

	str_i = 0;
	token_i = 0;
	while (data->str[str_i] != '\0')
	{
		if (is_unquoted_blank(data->str, str_i) == true)
			;
		else if (is_unquoted_operator_char(data->str, str_i))
		{
			create_operator(data->str, &(data->token_arr[token_i]), &str_i);
			token_i++;
		}
		else
		{
			if (create_word(data->str, &(data->token_arr[token_i]), &str_i) < 0)
				return (-1);
			token_i++;
		}
		str_i++;
	}
	return (0);
}
