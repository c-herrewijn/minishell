/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_count_tokens.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 21:23:55 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/05/17 21:55:53 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_tokens_delimited(size_t *word_count, t_lexer_state *state,
	char *str, size_t index)
{
	if (is_unquoted_blank(str, index) == true)
		*state = DELIMITED;
	else if (is_unquoted_operator_char(str, index))
	{
		*state = READING_OPERATOR;
		(*word_count)++;
	}
	else
	{
		*state = READING_WORD;
		(*word_count)++;
	}
}

void	count_tokens_reading_operator(size_t *word_count, t_lexer_state *state,
	char *str, size_t index)
{
	if (is_unquoted_blank(str, index) == true)
		*state = DELIMITED;
	else if (is_double_operator(str[index - 1], str[index]))
		*state = DELIMITED;
	else if (is_unquoted_operator_char(str, index))
	{
		*state = READING_OPERATOR;
		(*word_count)++;
	}
	else
	{
		*state = READING_WORD;
		(*word_count)++;
	}
}

void	count_tokens_reading_word(size_t *word_count, t_lexer_state *state,
	char *str, size_t index)
{
	if (is_unquoted_blank(str, index) == true)
		*state = DELIMITED;
	else if (is_unquoted_operator_char(str, index))
	{
		*state = READING_OPERATOR;
		(*word_count)++;
	}
	else
		*state = READING_WORD;
}
