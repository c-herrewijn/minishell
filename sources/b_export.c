/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   b_export.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 12:26:47 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/07 17:06:02 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//if in, concat inplace
//if not in, append to the env linked list
int		b_export_concat(int argc, char **argv, char *str, t_node **head)
{
	char *without_plus;

	without_plus = remove_plus(argv[1]);
	if (without_plus == NULL)
		return (-1);
	if (empty_list_add(head, without_plus) == true)
		return 0;
	if (concat_helper(argc, make_is_in_env_compatible(without_plus), head, without_plus) == -1)
		return (-1);
	return (0);
}

//unset then export
int		b_export(int argc, char **argv, char *str, t_node **head)
{
	//cpy is basicly same as argv[1]
	//arr[0] is 'export name'
	//argv[0] export
	//argv[1] name=value
	char *cpy;
	char **arr;

	cpy = ft_substr(argv[1], 0, ft_strlen(argv[1]));
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
	b_unset(argc, argv, head);
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
