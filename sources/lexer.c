/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 12:44:41 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/05/22 12:04:56 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
