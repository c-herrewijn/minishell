/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 12:36:57 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/05/17 21:27:46 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_2d_array(char **s)
{
	int i;

	i = 0;
	while(s[i] != NULL)
	{
		printf("%s\n", s[i]);
		i++;
	}
}

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
