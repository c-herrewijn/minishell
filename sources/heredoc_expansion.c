/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_expansion.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/20 14:04:50 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/20 20:05:49 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_here_str(char **here_str, t_node *env)
{
	char *exp_str;
	
	exp_str = create_expanded_str(*here_str, env);
	if (exp_str == NULL)
		return (-1);
	free (*here_str);
	*here_str = exp_str;
	return (0);
}
