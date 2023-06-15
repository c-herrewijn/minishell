/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_pwd_env.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 22:13:45 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/15 18:31:37 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pwd_helper(t_node **head, char *cur_dir)
{
	t_node	*node;
	int		i;
	int		spot;

	node = *head;
	spot = index_in_env("nil", "PWD", head);
	i = 0;
	while (node->next != NULL && i < spot)
	{
		node = node->next;
		i++;
	}
	free(node->str);
	node->str = ft_strjoin("PWD=", cur_dir);
	if (node->str == NULL)
		return (-1);
	return (0);
}

//set env var PWD
//store return of getcwd
//very similiar situation to b_export_concat_inplace
int	update_pwd(t_node **head)
{
	int		total;
	char	cur_dir[PATH_MAX];

	total = pwd_in_env(head);
	if (total <= 1)
		return (0);
	if (getcwd(cur_dir, sizeof(cur_dir)) == NULL)
	{
		printf("ERROR : getcwd fail\n");
		return (0);
	}
	if (pwd_helper(head, cur_dir) == -1)
		return (-1);
	return (0);
}
