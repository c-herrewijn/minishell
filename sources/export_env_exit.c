/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_env_exit.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 22:40:04 by kkroon        #+#    #+#                 */
/*   Updated: 2023/05/30 21:37:26 by kkroon        ########   odam.nl         */
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

char	*remove_plus(char *str)
{
	char *new;
	int i;
	int j;
	int flag;
	int elen;

	elen = (int)ft_strlen("export ");
	i = elen;
	j = 0;
	flag = 0;
	new = malloc(((int)ft_strlen(str)) - elen + 1);
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

// yep
// malloc len of both
//loop through
void	b_export_concat_inplace(char *str, t_node **head, int spot)
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
	free(node->str);
	node->str = temp;
	return ;
}

//if in, concat inplace
//if not in, append to the env linked list
void	b_export_concat(char *str, t_node **head)
{
	int spot;
	char *without_plus;
	char **arr;
	char *with_prefix;

	if (*head == NULL)
	{
		printf("*head == NULL it seems\n");
		return ;
	}
	without_plus = remove_plus(str); //also without export
	if (empty_list_add(head, without_plus) == true)
		return ;
	with_prefix = ft_strjoin("export ", without_plus);
	arr = ft_split(with_prefix,'=');
	spot = is_in_env(arr[0], head, 2);
	free_double_char_pointer(arr);
	if (spot == -1)
	{
		printf("concat : spot == -1 : %s\n", without_plus);
		list_append(head, without_plus);
		return ;
	}
	b_export_concat_inplace(without_plus, head, spot);
}

//unset then export
//might want to update existing env var in place if it already exists
void	b_export(char *str, t_node **head)
{
	char *cpy;
	int slen;
	int elen;
	int listlen;
	char **arr;

	if (*head == NULL)
	{
		printf("*head == NULL it seems\n");
		return ;
	}
	listlen = list_len(*head);
	slen = (int)ft_strlen(str);
	elen = (int)ft_strlen("export ");
	cpy = ft_substr(str, elen, slen - elen);
	if (empty_list_add(head, cpy) == true)
		return ;
	arr = ft_split(str,'=');
	b_unset(arr[0], head, 2);
	free_double_char_pointer(arr);
	if (empty_list_add(head, cpy) == true)
		return ;
	list_append(head, cpy);
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
