/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstdelone.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 15:09:06 by cherrewi      #+#    #+#                 */
/*   Updated: 2022/10/23 13:31:21 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
deletest the content of the node, by applying functtion (del)
then deletes the node
*/
void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst && del)
	{
		if (lst->content && del)
			del(lst->content);
		free(lst);
	}
}
