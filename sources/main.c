/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 12:36:57 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/21 20:11:27 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// debug
void	check_leaks(void)
{
	system("leaks minishell");
}

// debug
// atexit(check_leaks);
// printf("data.str = %s\n", data.str);
// print_tokens(&data);
// print_commands(&data);
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	signumber = 0;
	init_data_struct(&data, argc, argv, envp);
	if (list_create_env(&data.head, data) < 0)
		free_and_exit_with_perror(&data, &data.head);
	if (update_shlvl(&data.head) < 0)
		free_and_exit_with_perror(&data, &data.head);
	main_loop(data);
	return (0);
}
