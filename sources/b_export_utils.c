/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   b_export_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/02 20:47:48 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/08 13:30:37 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	empty_list_add(t_node **head, char *str)
{
	int listlen;

	listlen = list_len(*head);
	if (listlen == 1 && (*head)->str == NULL)
	{
		(*head)->str = str;
		(*head)->next = NULL;
		return true;
	}
	return false;
}

// gives back str as name=value, without +=
char	*remove_plus(char *str)
{
	char *new;
	int i;
	int j;
	int flag;

	i = 0;
	j = 0;
	flag = 0;
	new = malloc(((int)ft_strlen(str)));
	if (new == NULL)
		return (NULL);
	while(str[i] != '\0')
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
	return new;
}

//already in
int		b_export_concat_inplace(char *str, t_node **head, int spot)
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
	return 0;
}

int	concat_helper(int argc, char **argv, t_node **head, char *without_plus)
{
	int spot;
	char *cpy;

	spot = is_in_env(argc, argv, head);
	cpy = ft_substr(without_plus, 0, ft_strlen(without_plus));
	free(argv[1]);
	free(argv);
	if (cpy == NULL)
		return (-1);
	if (spot == -1)
	{
		printf("concat : spot == -1 : %s\n", cpy);
		if (list_append(head, cpy) == -1)
			return (-1);
		return (0);
	}
	if (b_export_concat_inplace(cpy, head, spot) == -1)
		return (-1);
	return (0);
}
