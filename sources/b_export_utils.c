/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   b_export_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 20:47:48 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/12 16:01:30 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	empty_list_add(t_node **head, char *str)
{
	int	listlen;

	listlen = list_len(*head);
	if (listlen == 1 && (*head)->str == NULL)
	{
		(*head)->str = str;
		(*head)->next = NULL;
		return (true);
	}
	return (false);
}

// gives back str as name=value, without +=
char	*remove_plus(char *str)
{
	char	*new;
	int		i;
	int		j;
	int		flag;

	i = 0;
	j = 0;
	flag = 0;
	new = malloc(((int)ft_strlen(str)));
	if (new == NULL)
		return ((NULL));
	while (str[i] != '\0')
	{
		if (str[i] == '+' && flag == 0)
			flag = 1;
		else
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}

//already in
int	b_export_concat_inplace(char *str, t_node **head, int spot)
{
	t_node	*node;
	int		i;
	int		x;
	char	*temp;

	node = *head;
	i = 0;
	while (node->next != NULL && i < spot)
	{
		node = node->next;
		i++;
	}
	x = index_of_c_in_str(str, '=');
	temp = ft_strjoin(node->str, str + x + 1);
	if (temp == NULL)
		return (-1);
	free(node->str);
	node->str = temp;
	return (0);
}

int	concat_helper(int argc, char **argv, t_node **head, char *without_plus)
{
	int	spot;

	spot = index_in_env(argv[0], without_plus, head);
	if (spot == -1)
	{
		printf("concat : spot == -1 : %s\n", without_plus);
		if (list_append(head, without_plus) == -1)
			return (-1);
		return (0);
	}
	if (b_export_concat_inplace(without_plus, head, spot) == -1)
		return (-1);
	return (0);
}
