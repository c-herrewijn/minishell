/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 14:28:40 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/15 14:20:40 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// returns the index of the variable name, or -1 if not found
// a return >= 0 means str is an environment variable
int	find_str_in_environment(t_node *env, char *str)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		if (ft_strncmp(str, env->str, ft_strlen(str)) == 0)
			return (i);
		i++;
		env = env->next;
	}
	return (-1);
}

char *get_value_from_env(t_node *env, char *str)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		if (ft_strncmp(str, env->str, ft_strlen(str)) == 0)
			return(env->str + ft_strlen(str) + 1);
		i++;
		env = env->next;
	}
	return (NULL);
}

size_t var_len(char *var_name, t_node *head)
{
	char 	*value;
	size_t	len;

	value = get_value_from_env(head, var_name);
	len = ft_strlen(value);
	
	// printf("val name: %s\n", var_name);
	// printf("val value: %s\n", value);
	// printf("val length: %zu\n", len);
	
	return (len);
	// return ft_strlen(get_value_from_env(head, var_name));
}

/*
NOTE: 
- trailing and leading blanks have already been stripped in tokenizing / parsing
- exception: '$' followed by a blank, '\0' or '$' is literally printed
*/
size_t expanded_str_len(char *in_str, t_node *env_node)
{
	t_expander_state	expander_state;
	size_t				i;
	size_t				len;
	size_t				var_start_index;
	char				*var_name;

	char				c; // debug

	expander_state = SCANNING;
	i = 0;
	len = 0;
	var_start_index = 0;
	while(true)
	{
		c = in_str[i];  // debug
		if (expander_state == SCANNING)
		{
			if (in_str[i] == '\'')
			{
				expander_state = LITERAL_SCANNING;
			}
			else if (in_str[i] == '\"')
			{
				;
			}
			else if (in_str[i] == '$')
			{
				expander_state = READING_VAR_NAME;
				var_start_index = i + 1;
			}
			// else if (ft_isblank(in_str[i]))
			// {

			// }
			else if (in_str[i] == '\0')
			{
				break;
			}
			else	// normal chars incl. blanks
			{
				len+=1;
			}
		}
		else if (expander_state == LITERAL_SCANNING)
		{
			if (in_str[i] == '\'')
			{
				expander_state = SCANNING;
			}
			else if (in_str[i] == '\0')  // should not happen, since quotes always need to be terminated
			{
				break;
			}
			else
			{
				len+=1;
			}
		}
		// state READING_VAR_NAME is only used in scenarios where $ is followed by a char other than:
		// - single quote
		// - double quote
		// - another $ sign
		// - blank (i.e. space or tab)
		// - '\0'
		else if (expander_state == READING_VAR_NAME)
		{

			if (in_str[i] == '\'')
			{
				var_name = ft_substr(in_str, var_start_index, i - var_start_index); // todo malloc protection
				len += var_len(var_name, env_node);
				expander_state = LITERAL_SCANNING;
			}
			else if (in_str[i] == '\"')
			{
				if (i != var_start_index)
				{
					var_name = ft_substr(in_str, var_start_index, i - var_start_index); // todo malloc protection
					len += var_len(var_name, env_node);
				}
				expander_state = SCANNING;
			}
			else if (in_str[i] == '$')
			{
				if (i == var_start_index)
					len++;		// literally print $ char
				else
				{
					var_name = ft_substr(in_str, var_start_index, i - var_start_index); // todo malloc protection
					len += var_len(var_name, env_node);
				}
				expander_state = READING_VAR_NAME;
				var_start_index = i + 1;
			}
			else if (ft_isblank(in_str[i]))
			{
				if (i == var_start_index)
					len++;		// literally print $ char
				else
				{
					var_name = ft_substr(in_str, var_start_index, i - var_start_index); // todo malloc protection
					len += var_len(var_name, env_node);
				}
				len++;		// print blank
				expander_state = SCANNING;
			}
			else if (in_str[i] == '\0')
			{
				if (i == var_start_index)
					len++;		// literally print $ char
				else
				{
					var_name = ft_substr(in_str, var_start_index, i - var_start_index); // todo malloc protection
					len += var_len(var_name, env_node);
				}
				break;
			}
			else	// normal chars
			{
				;
			}	
		}
		i++;
	}
	return (len);
}


int	expander(t_data *data)
{
	if (data == NULL)  // dummy
		return (-1);  // dummy
	
	return (0);
}


// NOTE: if no command is executed (e.g. empty line), the exit status of the
//   previous command reamins in memory
void	store_final_exit_status(t_data *data)
{
	int	i_last;

	if (data->nr_commands >= 1)
	{
		i_last = data->nr_commands - 1;
		data->previous_exit_status = data->command_arr[i_last].exit_status;
	}
}
