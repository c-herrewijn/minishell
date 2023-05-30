/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_env_exit.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 22:40:04 by kkroon        #+#    #+#                 */
/*   Updated: 2023/05/30 17:16:52 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//need to check for malloc fails
//need to free things i don't return
char	*remove_plus(char *str)
{
	char **arr;
	char *new;

	arr = ft_split(str, ' ');	
	new = ft_strjoin(arr[0], arr[1]);
	free_double_char_pointer(arr);
	return new;
}

void	b_export_concat_inplace(char *str, t_node **head, int spot)
{
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
	spot = is_in_env(str, head, 2);
	without_plus = remove_plus(str);
	if (spot == -1)
	{
		if (listlen == 1 && (*head)->str == NULL)
		{
			(*head)->str = without_plus;
			(*head)->next = NULL;
		}
		else
			list_append(head, without_plus);
		return ;
	}
	//else concat in place
	//how to concat,
	//get spot, split on =, join everything step for step
	
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
