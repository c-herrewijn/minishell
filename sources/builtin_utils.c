/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 15:53:59 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/26 22:59:48 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_char_pointer(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

// get length of double char pointer
int	b_arr_len(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
	{
		i++;
	}
	return (i);
}

/*
returns:
0 : no OLDPWD, no PWD
1 : yes OLDPWD, no PWD
2 : no OLDPWD, yes PWD
3 : yes OLDPWD, yes PWD
*/
int	pwd_in_env(t_node **head)
{
	int	total;

	total = 0;
	if (index_in_env("nil", "OLDPWD", head) >= 0)
		total += 1;
	if (index_in_env("nil", "PWD", head) >= 0)
		total += 2;
	return (total);
}

t_node	*get_node_from_index(t_node **head, int index)
{
	t_node	*node;
	int		x;

	x = 0;
	node = *head;
	while (node->next != NULL && x < index)
	{
		node = node->next;
		x++;
	}
	return (node);
}
