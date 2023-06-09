/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 14:28:40 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/09 15:20:24 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
