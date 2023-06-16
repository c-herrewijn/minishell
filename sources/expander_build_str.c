/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_build_str.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/16 13:19:14 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/16 17:16:39 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// NOTE: unprotected string append!!
// enough space should be malloced so the char can be appended
void append_str_with_char(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	str[i] = c;
	str[i + 1] = '\0';
}

void exp_state_scanning(char *in_str, char *exp_str, t_expander_data *exp_data)
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

// todo: check: can in_str be NULL?
char *malloc_expand_str(char *in_str, t_expander_data *exp_data, t_node *env_node)
{
	size_t	expanded_len;
	char	*expanded_str;

	expanded_len = expanded_str_len(in_str, env_node);
	expanded_str = malloc((expanded_len + 1) * sizeof(char));
	if (expanded_str == NULL)
		return (NULL);
	return (expanded_str);
}

/*
NOTE: trailing and leading blanks have already been stripped
in tokenizing / parsing
*/
char	*create_expanded_str(char *in_str, t_node *env_node)
{
	// size_t				i;	// i used to loop over in_str
	// size_t				i_exp_str;
	t_expander_data		exp_data;
	char				*exp_str;
	
	// i_exp_str = 0;
	exp_data.state = SCANNING;
	exp_data.i = 0;
	exp_data.var_start_index = 0;
	exp_str = malloc_expand_str(in_str, &exp_data, env_node);  // todo FREE
	exp_data.quote_state = OUT_OF_QUOTES;
	while (true)
	{
		if (exp_data.state == SCANNING)
		{
			exp_state_scanning(in_str, exp_str, &exp_data);
		}
		if (exp_data.state == READING_VAR_NAME)
		{
			;  // todo;
		}
		if (in_str[exp_data.i] == '\0')
			break ;
		update_quote_state(&exp_data, in_str[exp_data.i]);
		(exp_data.i)++;
	}
	return (exp_str);
}

