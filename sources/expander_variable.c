/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_variable.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/20 11:25:02 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/26 22:45:47 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_variable(char *in_str, char *exp_str, t_node *env_node,
	t_expander_data *exp_data)
{
	size_t	env_key_len;
	char	*env_value;
	size_t	env_value_len;
	size_t	i;

	env_key_len = exp_data->i - exp_data->var_start_index;
	env_value = get_value_from_env(env_node,
			in_str + exp_data->var_start_index, env_key_len);
	env_value_len = expander_var_len(in_str, exp_data, env_node);
	i = 0;
	while (i < env_value_len)
	{
		append_str_with_char(exp_str, env_value[i]);
		i++;
	}
}

void	exp_var_quote(char *in_str, char *exp_str, t_node *env_node,
	t_expander_data *exp_data)
{
	bool	print_quote;
	bool	print_dollar;

	exp_data->state = SCANNING;
	print_quote = 0;
	print_dollar = 0;
	if (in_str[exp_data->i] == '\'' && exp_data->quote_state == IN_DQUOTE)
		print_quote = 1;
	if (exp_data->i == exp_data->var_start_index
		&& exp_data->quote_state == IN_DQUOTE)
		print_dollar = 1;
	if (exp_data->i == exp_data->var_start_index)
	{
		if (print_dollar == true)
			append_str_with_char(exp_str, '$');
		if (print_quote == true)
			append_str_with_char(exp_str, in_str[exp_data->i]);
	}
	else
	{
		append_variable(in_str, exp_str, env_node, exp_data);
		if (print_quote == true)
			append_str_with_char(exp_str, in_str[exp_data->i]);
	}
}

// if consequtive dollars -> literally print first $ char
// NOTE: this is different from BASH, wher '$$' has special purpose
void	exp_var_dollar(char *in_str, char *exp_str, t_node *env_node,
	t_expander_data *exp_data)
{
	exp_data->state = READING_VAR_NAME;
	if (exp_data->i == exp_data->var_start_index)
	{
		exp_data->var_start_index = exp_data->i + 1;
		append_str_with_char(exp_str, '$');
	}
	else
	{
		append_variable(in_str, exp_str, env_node, exp_data);
		exp_data->var_start_index = exp_data->i + 1;
	}
}

// if blank or special char is directly after $ sign -> literally print $ char
void	exp_var_non_valid_char(char *in_str, char *exp_str, t_node *env_node,
	t_expander_data *exp_data)
{
	exp_data->state = SCANNING;
	if (exp_data->i == exp_data->var_start_index)
	{
		append_str_with_char(exp_str, '$');
		append_str_with_char(exp_str, in_str[exp_data->i]);
	}
	else
	{
		append_variable(in_str, exp_str, env_node, exp_data);
		append_str_with_char(exp_str, in_str[exp_data->i]);
	}
}

// if terminator is directly after $ sign -> literally print $ char
void	exp_var_terminator(char *in_str, char *exp_str, t_node *env_node,
	t_expander_data *exp_data)
{
	if (exp_data->i == exp_data->var_start_index)
		append_str_with_char(exp_str, '$');
	else
	{
		append_variable(in_str, exp_str, env_node, exp_data);
	}
}
