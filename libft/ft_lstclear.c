/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 15:08:56 by cherrewi      #+#    #+#                 */
/*   Updated: 2022/10/23 13:30:55 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
deletes all nodes in a linked list after and including lst
the content fo the nodes is deleted by function del
*/
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next;
	t_list	*first;

	if (lst && del)
	{
		first = *lst;
		while (*lst)
		{
			next = (*lst)->next;
			if (next == first)
				break ;
			ft_lstdelone(*lst, del);
			*lst = next;
		}
	}
}
