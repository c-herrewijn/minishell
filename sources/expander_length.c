/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_length.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 16:51:21 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/16 17:12:11 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_quote_state(t_expander_data *exp_data, char c)
{
	if (c == '\'' && exp_data->quote_state == OUT_OF_QUOTES)
		exp_data->quote_state = IN_SQUOTE;
	else if (c == '\'' && exp_data->quote_state == IN_SQUOTE)
		exp_data->quote_state = OUT_OF_QUOTES;
	else if (c == '\"' && exp_data->quote_state == OUT_OF_QUOTES)
		exp_data->quote_state = IN_DQUOTE;
	else if (c == '\"' && exp_data->quote_state == IN_DQUOTE)
		exp_data->quote_state = OUT_OF_QUOTES;
}

/*
processes 1 char at a time:
- normal chars and blanks are copied
- single and double quotes are stripped
- '$' switches to state READING_VAR_NAME
- single quote switches to state SQUOTE_SCANNING
*/
size_t	len_state_scanning(char *in_str, t_expander_data *exp_data)
{
	size_t	len;

	len = 0;
	if (in_str[exp_data->i] == '\'' && exp_data->quote_state == IN_DQUOTE)
		len = 1;
	if (in_str[exp_data->i] == '\"' && exp_data->quote_state == IN_SQUOTE)
		len = 1;
	else if (in_str[exp_data->i] == '$')
	{
		if (exp_data->quote_state == IN_SQUOTE)
			len = 1;
		else
		{
			exp_data->state = READING_VAR_NAME;
			exp_data->var_start_index = exp_data->i + 1;
		}
	}
	if (in_str[exp_data->i] != '\0' && in_str[exp_data->i] != '\''
			&& in_str[exp_data->i] != '\"' && in_str[exp_data->i] != '$')
		len = 1;
	return (len);
}

size_t	len_state_reading_var_name(char *in_str, t_node *env_node,
	t_expander_data *exp_data)
{
	if (in_str[exp_data->i] == '\'')
		return (len_squote(in_str, env_node, exp_data));
	else if (in_str[exp_data->i] == '\"')
		return (len_dquote(in_str, env_node, exp_data));
	else if (in_str[exp_data->i] == '$')
		return (len_dollar(in_str, env_node, exp_data));
	else if (ft_isblank(in_str[exp_data->i]))
		return (len_blank(in_str, env_node, exp_data));
	else if (in_str[exp_data->i] == '\0')
		return (len_terminator(in_str, env_node, exp_data));
	return (0);
}

/*
NOTE: trailing and leading blanks have already been stripped
in tokenizing / parsing
*/
size_t	expanded_str_len(char *in_str, t_node *env_node)
{
	size_t				len;
	t_expander_data		exp_data;

	len = 0;
	exp_data.state = SCANNING;
	exp_data.i = 0;
	exp_data.var_start_index = 0;
	exp_data.quote_state = OUT_OF_QUOTES;
	while (true)
	{
		if (exp_data.state == SCANNING)
			len += len_state_scanning(in_str, &exp_data);
		if (exp_data.state == READING_VAR_NAME)
			len += len_state_reading_var_name(in_str, env_node, &exp_data);
		if (in_str[exp_data.i] == '\0')
			break ;
		update_quote_state(&exp_data, in_str[exp_data.i]);
		(exp_data.i)++;
	}
	return (len);
}
