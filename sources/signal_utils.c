/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/16 17:07:52 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/21 20:15:18 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void signal_handler(int signum)
{
	signumber = signum;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void sig_heredoc(int signum)
{
	printf("\n");
}

int signumber_check(t_data *data)
{
	if (signumber == SIGINT)
	{
		signumber = 0;
		free_data(data);
		return (1);
	}
	return (0);
}
