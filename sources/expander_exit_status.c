/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_exit_status.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 11:17:35 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/22 11:18:10 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// assumes exit status in range [0-255]
void	exp_var_exit_status(char *in_str, char *exp_str, t_data *data,
	t_expander_data *exp_data)
{
	int		nr_part;

	exp_data->state = SCANNING;
	if (exp_data->i == exp_data->var_start_index)
	{
		nr_part = data->previous_exit_status;
		if (data->previous_exit_status > 100)
		{
			append_str_with_char(exp_str, '0' + nr_part / 100);
			nr_part = nr_part - ((nr_part / 100) * 100);
		}
		if (data->previous_exit_status > 10)
		{
			append_str_with_char(exp_str, '0' + nr_part / 10);
			nr_part = nr_part - ((nr_part / 10) * 10);
		}
		append_str_with_char(exp_str, '0' + nr_part);
	}
	else
	{
		append_variable(in_str, exp_str, data->head, exp_data);
		append_str_with_char(exp_str, in_str[exp_data->i]);
	}
}
