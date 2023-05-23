/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 12:36:57 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/05/23 12:28:44 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_node	*head;

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
		lexer(&data);
		// debug
		// printf("%s\n", data.str);
		
		check_if_builtin(data.str, &head);

		//debug
		// print_tokens(data.token_arr, &data);

		free_tokens(data.token_arr, &data);
		free(data.str);
	}
	return (0);
}
