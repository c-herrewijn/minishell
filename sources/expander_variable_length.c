/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_variable_length.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/16 11:57:22 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/20 21:53:51 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	len_squote(char *in_str, t_node *env_node, t_expander_data *exp_data)
{
	exp_data->state = SCANNING;
	if (exp_data->i != exp_data->var_start_index)
	{
		return (expander_var_len(in_str, exp_data, env_node));
	}
	return (0);
}

size_t	len_dquote(char *in_str, t_node *env_node, t_expander_data *exp_data)
{
	exp_data->state = SCANNING;
	if (exp_data->i != exp_data->var_start_index)
	{
		return (expander_var_len(in_str, exp_data, env_node));
	}
	return (0);
}

// if consequtive dollars -> literally print first $ char
// NOTE: this is different from BASH, wher '$$' has special purpose
size_t	len_dollar(char *in_str, t_node *env_node, t_expander_data *exp_data)
{
	size_t	env_var_len;

	exp_data->state = READING_VAR_NAME;
	if (exp_data->i == exp_data->var_start_index)
	{
		exp_data->var_start_index = exp_data->i + 1;
		return (1);
	}
	else
	{
		env_var_len = expander_var_len(in_str, exp_data, env_node);
		exp_data->var_start_index = exp_data->i + 1;
		return (env_var_len);
	}
}

// if blank is directly after $ sign -> literally print $ char and the new char
size_t	len_var_non_valid_char(char *in_str, t_node *env_node, t_expander_data *exp_data)
{
	exp_data->state = SCANNING;	
	if (exp_data->i == exp_data->var_start_index)
		return (2);
	else
	{
		return (expander_var_len(in_str, exp_data, env_node) + 1);
	}
}

// if terminator is directly after $ sign -> literally print $ char
size_t	len_terminator(char *in_str, t_node *env_node,
	t_expander_data *exp_data)
{
	if (exp_data->i == exp_data->var_start_index)
		return (1);
	else
	{
		return (expander_var_len(in_str, exp_data, env_node));
	}
}

// if ? is directly after $, add status code
// else expand the variable and add the '?' char literal
size_t	len_exit_status(char *in_str, t_node *env_node,
	t_expander_data *exp_data, t_data *data)
{
	size_t	nr_len;
	int		nr_part;
	
	exp_data->state = SCANNING;
	if (exp_data->i == exp_data->var_start_index)
	{
		nr_len = 1;
		nr_part = data->previous_exit_status;
		while (nr_part >= 10)
		{
			nr_part /= 10;
			nr_len += 1;
		}
		return (nr_len);
	}
	else
	{
		return (expander_var_len(in_str, exp_data, env_node) + 1);
	}
}
