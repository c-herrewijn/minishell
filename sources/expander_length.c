/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_length.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 16:51:21 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/15 18:14:28 by cherrewi      ########   odam.nl         */
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
size_t	get_length_state_scanning(char *in_str, t_expander_state *expander_state,
	size_t i, size_t *var_start_index)
{
	if (in_str[i] == '\'')
	{
		*expander_state = LITERAL_SCANNING;
		return (0);
	}
	else if (in_str[i] == '\"')
		return (0);
	else if (in_str[i] == '$')
	{
		*expander_state = READING_VAR_NAME;
		*var_start_index = i + 1;
		return (0);
	}
	else if (in_str[i] == '\0')
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
	t_expander_state *expander_state, size_t i)
{
	if (in_str[i] == '\'')
	{
		*expander_state = SCANNING;
		return (0);
	}
	else if (in_str[i] == '\0') 
		return (0);
	else
		return (1);
}

size_t	get_length_reading_var_name(char *in_str, t_expander_state *expander_state,
	size_t i, size_t *var_start_index, t_node *env_node)
{
	char *var_name;
	
	if (in_str[i] == '\'')
	{
		*expander_state = LITERAL_SCANNING;
		var_name = ft_substr(in_str, *var_start_index, i - *var_start_index); // todo malloc protection
		return (env_var_len(var_name, env_node));
	}
	else if (in_str[i] == '\"')
	{
		*expander_state = SCANNING;
		if (i != *var_start_index)
		{
			var_name = ft_substr(in_str, *var_start_index, i - *var_start_index); // todo malloc protection
			return (env_var_len(var_name, env_node));
		}
		return (0);
	}
	else if (in_str[i] == '$')
	{
		*expander_state = READING_VAR_NAME;
		if (i == *var_start_index)
		{
			*var_start_index = i + 1;
			return (1);		// literally print $ char
		}
		else
		{
			var_name = ft_substr(in_str, *var_start_index, i - *var_start_index); // todo malloc protection
			*var_start_index = i + 1;
			return (env_var_len(var_name, env_node));
		}
	}
	else if (ft_isblank(in_str[i]))
	{
		*expander_state = SCANNING;
		if (i == *var_start_index)
			return (1);		// literally print $ char
		else
		{
			var_name = ft_substr(in_str, *var_start_index, i - *var_start_index); // todo malloc protection
			return (env_var_len(var_name, env_node) + 1);
		}
	}
	else if (in_str[i] == '\0')
	{
		if (i == *var_start_index)
			return (1);		// literally print $ char
		else
		{
			var_name = ft_substr(in_str, *var_start_index, i - *var_start_index); // todo malloc protection
			return (env_var_len(var_name, env_node));
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
size_t expanded_str_len(char *in_str, t_node *env_node)
{
	t_expander_state	expander_state;
	size_t				i;
	size_t				len;
	size_t				var_start_index;

	expander_state = SCANNING;
	i = 0;
	len = 0;
	var_start_index = 0;
	while(true)
	{
		if (expander_state == SCANNING)
		{
			len += get_length_state_scanning(in_str, &expander_state,
				i, &var_start_index);
		}
		else if (expander_state == LITERAL_SCANNING)
		{
			len += get_length_state_literal_scanning(in_str,
				&expander_state, i);
		}
		else if (expander_state == READING_VAR_NAME)
		{
			len += get_length_reading_var_name(in_str, &expander_state, i, &var_start_index, env_node);
		}
		if (in_str[i] == '\0')
			break;
		i++;
	}
	return (len);
}
