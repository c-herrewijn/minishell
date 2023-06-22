/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 14:28:40 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/22 10:14:57 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_value_from_env(t_node *env, char *key_str, size_t key_len)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		if (ft_strncmp(key_str, env->str, key_len) == 0 && env->str[key_len] == '=')
			return(env->str + key_len + 1);
		i++;
		env = env->next;
	}
	return (NULL);
}

/*
Input parameters:
- in_str: string that contains (somewhere in the string) a $ sign followed by
    an environmental variable keyword) 
- exp_data: data struct with following attributes:
  - exp_data->var_start_index: index of the start of the env variable name
     (directly after the $ sign)
  - exp_data->i: index of the character following the last character of the
     variable name
*/
size_t expander_var_len(char *in_str, t_expander_data *exp_data, t_node *env)
{
	size_t	key_len;
	size_t	value_len;
	char	*value;

	key_len = exp_data->i - exp_data->var_start_index;
	value = get_value_from_env(env, in_str + exp_data->var_start_index,
				key_len);
	value_len = ft_strlen(value);
	return (value_len);
}

int	expander(t_data *data)
{
	size_t 	i;
	size_t 	j;
	char	*exp_str;

	i = 0;
	while (i < data->nr_commands)
	{
		j = 0;
		while (j < data->command_arr[i].argc)
		{
			exp_str = create_expanded_str(data->command_arr[i].argv[j], data->head, data);
			if (exp_str == NULL)
				return (-1);
			free (data->command_arr[i].argv[j]);
			data->command_arr[i].argv[j] = exp_str;
			j++;
		}
		j = 0;
		while (data->command_arr[i].redirections[j] != NULL)
		{
			if (data->command_arr[i].redirections[j]->redirection_type != HEREDOC)	// todo: remove quotes from heredoc delimiter
			{
				exp_str = create_expanded_str(data->command_arr[i].redirections[j]->word, data->head, data);
				if (exp_str == NULL)
					return (-1);
				free (data->command_arr[i].redirections[j]->word);
				data->command_arr[i].redirections[j]->word = exp_str;
			}
			j++;
		}
		i++;
	}
	return (0);
}
