/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 21:24:00 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/05/17 21:26:38 by cherrewi      ########   odam.nl         */
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

// tests if char is <, >, | or the beginning of << or >>
static bool	is_operator(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

bool	is_unquoted_blank(char *str, size_t i)
{
	return (ft_isblank(str[i]) && is_unquoted_char(str, i));
}

bool	is_unquoted_operator_char(char *str, size_t i)
{
	return (is_operator(str[i]) && is_unquoted_char(str, i));
}

// tests if 2 chars form operators '<<' or '>>'
bool	is_double_operator(char c1, char c2)
{
	return ((c1 == '<' && c2 == '<')
		|| (c1 == '>' && c2 == '>'));
}
