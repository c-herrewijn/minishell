/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 12:44:41 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/05/17 21:55:53 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_tokens(char *str)
{
	size_t			word_count;
	size_t			i;
	t_lexer_state	state;

	state = DELIMITED;
	word_count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (state == DELIMITED)
			count_tokens_delimited(&word_count, &state, str, i);
		else if (state == READING_OPERATOR)
			count_tokens_reading_operator(&word_count, &state, str, i);
		else if (state == READING_WORD)
			count_tokens_reading_word(&word_count, &state, str, i);
		i++;
	}
	return (word_count);
}
