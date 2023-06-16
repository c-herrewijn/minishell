/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_length.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 16:51:21 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/16 11:49:28 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
processes 1 char at a time:
- normal chars and blanks are copied
- single and double quotes are stripped
- '$' switches to state READING_VAR_NAME
- single quote switches to state LITERAL_SCANNING
*/
size_t	get_length_state_scanning(char *in_str, t_expander_data *exp_data)
{
	if (in_str[exp_data->i] == '\'')
	{
		exp_data->state = LITERAL_SCANNING;
		return (0);
	}
	else if (in_str[exp_data->i] == '\"')
		return (0);
	else if (in_str[exp_data->i] == '$')
	{
		exp_data->state = READING_VAR_NAME;
		exp_data->var_start_index = exp_data->i + 1;
		return (0);
	}
	else if (in_str[exp_data->i] == '\0')
		return (0);
	else
		return (1);
}

/*
processes 1 char at a time:
- a single quote closes the literal string -> state is set to SCANNING
- '\0' should normally not happen, since that implies a dangling single quote
- other chars (incl. double quotes, pipes, $ sign etc) are processed literally
*/
size_t	get_length_state_literal_scanning(char *in_str,
	t_expander_data *exp_data)
{
	if (in_str[exp_data->i] == '\'')
	{
		exp_data->state = SCANNING;
		return (0);
	}
	else if (in_str[exp_data->i] == '\0') 
		return (0);
	else
		return (1);
}

size_t	get_length_reading_var_name(char *in_str, t_node *env_node,
	t_expander_data *exp_data)
{
	size_t env_var_len;
	
	if (in_str[exp_data->i] == '\'')
	{
		exp_data->state = LITERAL_SCANNING;
		return (expander_var_len(in_str, exp_data, env_node));
	}
	else if (in_str[exp_data->i] == '\"')
	{
		exp_data->state = SCANNING;
		if (exp_data->i != exp_data->var_start_index)
		{
			return (expander_var_len(in_str, exp_data, env_node));
		}
		return (0);
	}
	else if (in_str[exp_data->i] == '$')
	{
		exp_data->state = READING_VAR_NAME;
		if (exp_data->i == exp_data->var_start_index)
		{
			exp_data->var_start_index = exp_data->i + 1;
			return (1);		// literally print $ char
		}
		else
		{
			env_var_len = expander_var_len(in_str, exp_data, env_node);
			exp_data->var_start_index = exp_data->i + 1;
			return (env_var_len);
		}
	}
	else if (ft_isblank(in_str[exp_data->i]))
	{
		exp_data->state = SCANNING;
		if (exp_data->i == exp_data->var_start_index)
			return (1);		// literally print $ char
		else
		{
			return (expander_var_len(in_str, exp_data, env_node) + 1);
		}
	}
	else if (in_str[exp_data->i] == '\0')
	{
		if (exp_data->i == exp_data->var_start_index)
			return (1);		// literally print $ char
		else
		{
			return (expander_var_len(in_str, exp_data, env_node));
		}
	}
	else	// normal chars
	{
		return (0);
	}
}

/*
NOTE: trailing and leading blanks have already been stripped in tokenizing / parsing
*/
size_t	expanded_str_len(char *in_str, t_node *env_node)
{
	size_t				len;
	t_expander_data		exp_data;

	len = 0;
	exp_data.state = SCANNING;
	exp_data.i = 0;
	exp_data.var_start_index = 0;
	while (true)
	{
		if (exp_data.state == SCANNING)
			len += get_length_state_scanning(in_str, &exp_data);
		else if (exp_data.state == LITERAL_SCANNING)
			len += get_length_state_literal_scanning(in_str, &exp_data);
		else if (exp_data.state == READING_VAR_NAME)
			len += get_length_reading_var_name(in_str, env_node, &exp_data);
		if (in_str[exp_data.i] == '\0')
			break ;
		(exp_data.i)++;
	}
	return (len);
}
