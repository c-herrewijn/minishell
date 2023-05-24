/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_env_exit.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 22:40:04 by kkroon        #+#    #+#                 */
/*   Updated: 2023/05/24 22:34:39 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//unset then export
//might want to update existing env var in place if it already exists
void	b_export(char *str, t_node **head)
{
	b_unset(str, head);
	list_append(head, str + 7, 1);
}

//even need for b_env?
//probally need some error checking that env doesnt get any arguments
void	b_env(char *str, t_node *head)
{
	list_print(head);
}

//exit with errno and strerror/perror?
void	b_exit(int exit_status)
{
	exit(exit_status);
}
