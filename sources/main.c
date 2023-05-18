/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 12:36:57 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/05/18 16:50:48 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data data;
	data.argc = argc;
	data.argv = argv;
	data.envp = envp;

	while (true)
	{
		data.str = readline("minishell$ ");
		if (data.str == NULL)
			break ;
		add_history(data.str);
		// debug
		// printf("%s\n", data.str);
		
		check_if_builtin(data.str, envp);
	}
	return (0);
}
