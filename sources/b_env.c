/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   b_env.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 12:25:45 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/22 19:03:26 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//even need for b_env?
//probally need some error checking that env doesnt get any arguments
//what about if head == NULL, like the main node == NULL
int	b_env(t_node *head)
{
	t_node	*node;

	node = head;
	if (head == NULL)
		return (0);
	if (head->str == NULL)
		return (0);
	while (node != NULL)
	{
		printf("%s\n", node->str);
		node = node->next;
	}
	return (0);
}
