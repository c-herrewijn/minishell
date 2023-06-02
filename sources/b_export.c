/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   b_export.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 12:26:47 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/02 20:49:52 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//if in, concat inplace
//if not in, append to the env linked list
int		b_export_concat(char *str, t_node **head)
{
	char *without_plus;
	char **arr;
	char *with_prefix;

	without_plus = remove_plus(str);
	if (without_plus == NULL)
		return (-1);
	if (empty_list_add(head, without_plus) == true)
		return 0;
	with_prefix = ft_strjoin("export ", without_plus);
	if (with_prefix == NULL)
	{
		free(without_plus);
		return (-1);
	}
	arr = ft_split(with_prefix,'=');
	if (arr == NULL)
	{
		free(without_plus);
		free(with_prefix);
		return (-1);
	}
	if (concat_helper(arr, head, without_plus) == -1)
		return (-1);
	return (0);
}

//unset then export
//might want to update existing env var in place if it already exists
int		b_export(char *str, t_node **head)
{
	char *cpy;
	int slen;
	int elen;
	int listlen;
	char **arr;

	listlen = list_len(*head);
	slen = (int)ft_strlen(str);
	elen = (int)ft_strlen("export ");
	cpy = ft_substr(str, elen, slen - elen);
	if (cpy == NULL)
		return (-1);
	if (empty_list_add(head, cpy) == true)
		return (0);
	arr = ft_split(str,'=');
	if (arr == NULL)
	{
		free(cpy);
		return (-1);
	}
	b_unset(arr[0], head, 2);
	free_double_char_pointer(arr);
	if (empty_list_add(head, cpy) == true)
		return (0);
	if (list_append(head, cpy) == -1)
	{
		free(cpy);
		return (-1);		
	}
	return (0);
}
