/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlast.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 15:09:45 by cherrewi      #+#    #+#                 */
/*   Updated: 2022/10/19 15:09:47 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*lst_i;

	if (lst == NULL)
		return (NULL);
	lst_i = lst;
	while (lst_i->next && lst_i->next != lst)
		lst_i = lst_i->next;
	return (lst_i);
}
