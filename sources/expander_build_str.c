/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_build_str.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/16 13:19:14 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/22 11:25:48 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// NOTE: unprotected string append!!
// enough space should be malloced so the char can be appended
void	append_str_with_char(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	str[i] = c;
	str[i + 1] = '\0';
}

static char	*malloc_expand_str(char *in_str, t_node *env_node, t_data *data)
{
	size_t	expanded_len;
	char	*expanded_str;

	// todo: check: can in_str be NULL?
	expanded_len = expanded_str_len(in_str, env_node, data);
	expanded_str = malloc((expanded_len + 1) * sizeof(char));  // TODO: free malloc / error handling
	if (expanded_str == NULL)
		return (NULL);
	expanded_str[0] = '\0';
	return (expanded_str);
}

static void	exp_state_reading_var_name(char *in_str, char *exp_str,
	t_expander_data *exp_data, t_data *data)
{
	t_node	*env_node;

	env_node = data->head;
	if (in_str[exp_data->i] == '\'')
		exp_var_quote(in_str, exp_str, env_node, exp_data);
	else if (in_str[exp_data->i] == '\"')
		exp_var_quote(in_str, exp_str, env_node, exp_data);
	else if (in_str[exp_data->i] == '$')
		exp_var_dollar(in_str, exp_str, env_node, exp_data);
	else if (in_str[exp_data->i] == '\0')
		exp_var_terminator(in_str, exp_str, env_node, exp_data);
	else if (in_str[exp_data->i] == '?')
		return (exp_var_exit_status(in_str, exp_str, data, exp_data));
	else if (!ft_isalnum(in_str[exp_data->i]) && in_str[exp_data->i] != '_')
		exp_var_non_valid_char(in_str, exp_str, env_node, exp_data);
}

static void	exp_state_scanning(char *in_str, char *exp_str, t_expander_data *exp_data)
{
	if (in_str[exp_data->i] == '\'' && exp_data->quote_state == IN_DQUOTE)
		append_str_with_char(exp_str, in_str[exp_data->i]);
	if (in_str[exp_data->i] == '\"' && exp_data->quote_state == IN_SQUOTE)
		append_str_with_char(exp_str, in_str[exp_data->i]);
	else if (in_str[exp_data->i] == '$')
	{
		if (exp_data->quote_state == IN_SQUOTE)
			append_str_with_char(exp_str, in_str[exp_data->i]);
		else
		{
			exp_data->state = READING_VAR_NAME;
			exp_data->var_start_index = exp_data->i + 1;
		}
	}
	if (in_str[exp_data->i] != '\0' && in_str[exp_data->i] != '\''
		&& in_str[exp_data->i] != '\"' && in_str[exp_data->i] != '$')
		append_str_with_char(exp_str, in_str[exp_data->i]);
}

/*
NOTE: trailing and leading blanks have already been stripped
in tokenizing / parsing
*/
char	*create_expanded_str(char *in_str, t_node *env_node, t_data *data)
{
	t_expander_data		exp_data;
	char				*exp_str;

	exp_data.state = SCANNING;
	exp_data.i = 0;
	exp_data.var_start_index = 0;
	exp_data.quote_state = OUT_OF_QUOTES;
	exp_str = malloc_expand_str(in_str, env_node, data);  // todo FREE
	while (true)
	{
		if (exp_data.state == SCANNING)
			exp_state_scanning(in_str, exp_str, &exp_data);
		if (exp_data.state == READING_VAR_NAME)
			exp_state_reading_var_name(in_str, exp_str, &exp_data, data);
		if (in_str[exp_data.i] == '\0')
			break ;
		update_quote_state(&exp_data, in_str[exp_data.i]);
		(exp_data.i)++;
	}
	return (exp_str);
}
