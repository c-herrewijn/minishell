/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 15:09:58 by cherrewi      #+#    #+#                 */
/*   Updated: 2022/10/23 13:33:16 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_first;
	t_list	*i_new_list;
	t_list	*temp;

	if (!lst || !del || !f)
		return (NULL);
	new_first = ft_lstnew(f(lst->content));
	if (new_first == NULL)
		return (NULL);
	i_new_list = new_first;
	while (lst->next)
	{
		temp = ft_lstnew(f(lst->next->content));
		if (temp == NULL)
		{
			ft_lstclear(&new_first, del);
			return (NULL);
		}
		i_new_list->next = temp;
		i_new_list = i_new_list->next;
		lst = lst->next;
	}
	return (new_first);
}
