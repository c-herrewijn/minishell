/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_env_exit.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 22:40:04 by kkroon        #+#    #+#                 */
/*   Updated: 2023/05/30 20:55:21 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	// printf("wacky\n");
	new[j] = '\0';
	// printf("new : %s\n", new);
	return new;
}

// yep
// malloc len of both
//loop through
void	b_export_concat_inplace(char *str, t_node **head, int spot)
{
	t_node *node;
	int i;

	node = *head;
	i = 0;
	while (node->next != NULL && i < spot)
	{
		node = node->next;
		i++;
	}
	// printf("looped, now at : %s\n", node->str);
	return ;
}

//prob want to use ft_strjoin with free inside the function
//if in, concat inplace
//if not in, append to the env linked list
void	b_export_concat(char *str, t_node **head)
{
	int listlen;
	int spot;
	char *without_plus;

	if (*head == NULL)
	{
		printf("*head == NULL it seems\n");
		return ;
	}
	listlen = list_len(*head);
	// printf("concat : past listlen\n");
	without_plus = remove_plus(str); //also without export
	if (listlen == 1 && (*head)->str == NULL)
	{
		printf("concat : listlen == 1\n");
		(*head)->str = without_plus;
		(*head)->next = NULL;
		return ;
	}
	//ft_strjoin("export ", without_plus)
	char *with_prefix;
	with_prefix = ft_strjoin("export ", without_plus);
	// printf("with_prefix : %s\n", with_prefix);
	spot = is_in_env(with_prefix, head, 2);
	if (spot == -1) // always the case if using without_plus, without export prefix
	{
		printf("concat : spot == -1 : %s\n", without_plus);
		list_append(head, without_plus);
		return ;
	}
	//else concat in place
	//how to concat,
	//get spot, split on =, join everything step for step
	b_export_concat_inplace(without_plus, head, spot);
	// printf("concat : end of func\n");
}

//unset then export
//might want to update existing env var in place if it already exists
void	b_export(char *str, t_node **head)
{
	char *cpy;
	int slen;
	int elen;
	int listlen;

	if (*head == NULL)
	{
		printf("*head == NULL it seems\n");
		return ;
	}
	listlen = list_len(*head);
	slen = (int)ft_strlen(str);
	elen = (int)ft_strlen("export ");
	cpy = ft_substr(str, elen, slen - elen);
	if (listlen == 1 && (*head)->str == NULL)
	{
		(*head)->str = cpy;
		(*head)->next = NULL;
		return ;
	}
	b_unset(str, head, 2);
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
