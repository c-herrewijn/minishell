/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_oldpwd_env.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/12 17:07:36 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/12 17:08:02 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	oldpwd_helper(t_node **head)
{
	t_node	*pwdnode;
	t_node	*oldpwdnode;
	int		i;
	int		spot;

	i = 0;
	pwdnode = *head;
	oldpwdnode = *head;
	spot = index_in_env("test", "PWD", head);
	while (pwdnode->next != NULL && i < spot)
	{
		pwdnode = pwdnode->next;
		i++;
	}
	i = 0;
	spot = index_in_env("test", "OLDPWD", head);
	while (oldpwdnode->next != NULL && i < spot)
	{
		oldpwdnode = oldpwdnode->next;
		i++;
	}
	free(oldpwdnode->str);
	oldpwdnode->str = ft_strjoin("OLD", pwdnode->str);
	if (oldpwdnode->str == NULL)
		return (-1);
	return (0);
}

//very similiar situation to b_export_concat_inplace
//double check the deal with total
//just ft_strjoin "OLD" and node->str of PWD
int	update_oldpwd(t_node **head)
{
	int total;

	total = pwd_in_env(head);
	if (total <= 2)
	{
		printf("DEBUG : no PWD or OLDPWD present in env : total = %d\n", total);
		return 0;
	}
	if (oldpwd_helper(head) == -1)
		return (-1);
	return (0);
}