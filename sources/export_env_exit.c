/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_env_exit.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 22:40:04 by kkroon        #+#    #+#                 */
/*   Updated: 2023/05/25 20:30:31 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//unset then export
//might want to update existing env var in place if it already exists
void	b_export(char *str, t_node **head)
{
	char *cpy;
	int slen;
	int elen;

	slen = (int)ft_strlen(str);
	elen = (int)ft_strlen("export ");
	cpy = ft_substr(str, elen, slen - elen);
	b_unset(str, head, 2);
	list_append(head, cpy, 1);
}

//even need for b_env?
//probally need some error checking that env doesnt get any arguments
void	b_env(t_node *head)
{
	list_print(head);
}

//exit with errno and strerror/perror?
void	b_exit(int exit_status)
{
	exit(exit_status);
}
