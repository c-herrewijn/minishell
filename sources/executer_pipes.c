/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer_pipes.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 17:58:16 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/15 17:59:29 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipes(t_data *data)
{
	size_t	i;
	int		result;

	data->pipes = malloc(data->nr_pipes * 2 * sizeof(int));
	if (data->pipes == NULL)
		return (-1);
	i = 0;
	while (i < data->nr_pipes)
	{
		result = pipe(data->pipes[i]);
		if (result < 0)
		{
			free(data->pipes);
			data->pipes = NULL;
			return (-1);
		}
		i++;
	}
	return (0);
}

int	close_pipes_before_running_command_i(t_data *data, size_t i_command)
{
	size_t	i_pipe;

	i_pipe = 0;
	while (i_pipe < data->nr_pipes)
	{
		if (!(i_command == i_pipe + 1))
		{
			if (close(data->pipes[i_pipe][0]) < 0)
			{
				perror(NULL);
				return (-1);
			}
		}
		if (!(i_command == i_pipe))
		{
			if (close(data->pipes[i_pipe][1]) < 0)
			{
				perror(NULL);
				return (-1);
			}
		}
		i_pipe++;
	}
	return (0);
}

int	close_all_pipes(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nr_pipes)
	{
		if (close(data->pipes[i][0]) < 0)
		{
			perror(NULL);
			return (-1);
		}
		if (close(data->pipes[i][1]) < 0)
		{
			perror(NULL);
			return (-1);
		}
		i++;
	}
	return (1);
}