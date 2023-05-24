/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_count_tokens.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 21:23:55 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/05/24 22:04:34 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	count_tokens_delimited(size_t *token_count, t_lexer_state *state,
	char *str, size_t index)
{
	if (is_unquoted_blank(str, index) == true)
		*state = DELIMITED;
	else if (is_unquoted_operator_char(str, index))
	{
		*state = READING_OPERATOR;
		(*token_count)++;
	}
	else
	{
		*state = READING_WORD;
		(*token_count)++;
	}
}

static void	count_tokens_reading_operator(size_t *token_count,
	t_lexer_state *state, char *str, size_t index)
{
	if (is_unquoted_blank(str, index) == true)
		*state = DELIMITED;
	else if (is_double_operator(str[index - 1], str[index]))
		*state = DELIMITED;
	else if (is_unquoted_operator_char(str, index))
	{
		*state = READING_OPERATOR;
		(*token_count)++;
	}
	else
	{
		*state = READING_WORD;
		(*token_count)++;
	}
}

static void	count_tokens_reading_word(size_t *token_count,
	t_lexer_state *state, char *str, size_t index)
{
	if (is_unquoted_blank(str, index) == true)
		*state = DELIMITED;
	else if (is_unquoted_operator_char(str, index))
	{
		*state = READING_OPERATOR;
		(*token_count)++;
	}
	else
		*state = READING_WORD;
}

size_t	count_tokens(char *str)
{
	size_t			token_count;
	size_t			i;
	t_lexer_state	state;

	state = DELIMITED;
	token_count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (state == DELIMITED)
			count_tokens_delimited(&token_count, &state, str, i);
		else if (state == READING_OPERATOR)
			count_tokens_reading_operator(&token_count, &state, str, i);
		else if (state == READING_WORD)
			count_tokens_reading_word(&token_count, &state, str, i);
		i++;
	}
	return (token_count);
}
