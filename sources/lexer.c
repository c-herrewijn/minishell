/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 12:44:41 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/05/17 20:51:04 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
checks if char in a string is within single or double quotes or not
assumes the string does not contain unclosed single or double quotes
*/
static bool	is_unquoted_char(char *str, size_t index)
{
	size_t	i;
	bool	open_squote;
	bool	open_dquote;

	open_squote = false;
	open_dquote = false;
	i = 0;
	while (i < index)
	{
		if (str[i] == '\"' && open_squote == false)
			open_dquote = !open_dquote;
		if (str[i] == '\'' && open_dquote == false)
			open_squote = !open_squote;
		i++;
	}
	if (open_squote || open_dquote)
		return (false);
	else
		return (true);
}

bool	is_unquoted_blank(char *str, size_t i)
{
	return (ft_isblank(str[i]) && is_unquoted_char(str, i));
}

// tests if char is <, >, | or the beginning of << or >>
bool	is_operator(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

// tests if 2 chars form operators '<<' or '>>'
bool	is_double_operator(char c1, char c2)
{
	return ((c1 == '<' && c2 == '<')
		|| (c1 == '>' && c2 == '>'));
}

bool	is_unquoted_operator_char(char *str, size_t i)
{
	return (is_operator(str[i]) && is_unquoted_char(str, i));
}

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
		{
			if (is_unquoted_blank(str, i))
				;
			else if (is_unquoted_operator_char(str, i))
			{
				state = READING_OPERATOR;
				word_count++;
			}
			else
			{
				state = READING_WORD;
				word_count++;
			}
		}
		else if (state == READING_OPERATOR)
		{
			if (is_double_operator(str[i - 1], str[i]))
			{
				state = DELIMITED;
			}
			else if (is_unquoted_operator_char(str, i))
			{
				state = READING_OPERATOR;
				word_count++;
			}
			else if (is_unquoted_blank(str, i))
			{
				state = DELIMITED;
			}
			else
			{
				state = READING_WORD;
				word_count++;
			}
		}
		else if (state == READING_WORD)
		{
			if (is_unquoted_operator_char(str, i))
			{
				state = READING_OPERATOR;
				word_count++;
			}
			else if (is_unquoted_blank(str, i))
			{
				state = DELIMITED;
				continue ;
			}
			else
			{
				state = READING_WORD;
			}
		}
		i++;
	}
	return (word_count);
}
