/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 14:28:40 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/16 14:09:28 by cherrewi      ########   odam.nl         */
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


size_t expander_var_len(char *in_str, t_expander_data *exp_data, t_node *env)
{
	size_t	key_len;
	size_t	value_len;
	char	*value;

	key_len = exp_data->i - exp_data->var_start_index;
	value = get_value_from_env(env, in_str + exp_data->i - key_len, key_len);
	value_len = ft_strlen(value);
	return (value_len);
}

int	expander(t_data *data)
{
	if (data == NULL)  // dummy
		return (-1);  // dummy
	
	return (0);
}


// NOTE: if no command is executed (e.g. empty line), the exit status of the
//   previous command remains in memory
void	store_final_exit_status(t_data *data)
{
	int	i_last;

	if (data->nr_commands >= 1)
	{
		i_last = data->nr_commands - 1;
		data->previous_exit_status = data->command_arr[i_last].exit_status;
	}
}
