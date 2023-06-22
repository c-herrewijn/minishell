/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/16 17:07:52 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/22 11:38:31 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signum)
{
	g_signumber = signum;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_heredoc(int signum)
{
	// todo: what to do with input 'signum'
	(void) signum;
	printf("\n");
}

int	signumber_check(t_data *data)
{
	if (g_signumber == SIGINT)
	{
		g_signumber = 0;
		free_data(data);
		return (1);
	}
	return (0);
}
