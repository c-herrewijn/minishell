/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals2.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/21 20:14:28 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/21 20:14:35 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void set_signals_parent()
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void set_signals_heredoc()
{
	signal(SIGINT, sig_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void set_signals_default()
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void set_signals_blocked()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}