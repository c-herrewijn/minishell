/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 12:36:57 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/05/19 19:27:52 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data data;
	t_node *head;

	data.argc = argc;
	data.argv = argv;
	data.envp = envp;
	list_create_env(&head, data);
	while (true)
	{
		data.str = readline("minishell$ ");
		if (data.str == NULL)
			break ;
		add_history(data.str);
		// debug
		// printf("%s\n", data.str);
		
		check_if_builtin(data.str, &head);
	}
	return (0);
}
