/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstiter.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 15:09:25 by cherrewi      #+#    #+#                 */
/*   Updated: 2022/10/23 13:32:16 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*first;

	if (lst && f)
	{
		first = lst;
		while (lst)
		{
			f(lst->content);
			if (lst->next == first)
				break ;
			lst = lst->next;
		}
	}
}
