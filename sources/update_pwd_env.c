/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_pwd_env.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 22:13:45 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/10 17:06:59 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pwd_oldpwd_spot(t_node **head, int mode)
{
	int		pwdspot;
	int		oldpwdspot;

	pwdspot = index_in_env("test", "PWD", head);
	oldpwdspot = index_in_env("test", "OLDPWD", head);
	if (mode == 1)
		return pwdspot;
	return oldpwdspot;
}

// static void increment_linked_list(t_node **node)
// {
	
// }

static int	oldpwd_helper(t_node **head)
{
	t_node	*pwdnode;
	t_node	*oldpwdnode;
	int		i;
	int		spot;

	i = 0;
	pwdnode = *head;
	oldpwdnode = *head;
	spot = pwd_oldpwd_spot(head, 1);
	while (pwdnode->next != NULL && i < spot)
	{
		pwdnode = pwdnode->next;
		i++;
	}
	i = 0;
	spot = pwd_oldpwd_spot(head, 2);
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
	if (total == -1)
		return (-1);
	if (total <= 2)
	{
		printf("DEBUG : no PWD or OLDPWD present in env : total = %d\n", total);
		return 0;
	}
	if (oldpwd_helper(head) == -1)
		return (-1);
	return (0);
}

static int	pwd_helper(t_node **head, char *cur_dir)
{
	t_node	*node;
	int		i;
	int		spot;

	node = *head;
	spot = index_in_env("test", "PWD", head);
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
	if (total == -1)
		return (-1);
	if (total == 0 || total == 1)
	{
		printf("DEBUG : no PWD present in env : total = %d\n", total);
		return 0;
	}
	if (getcwd(cur_dir, sizeof(cur_dir)) == NULL)
	{
		printf("ERROR : getcwd fail\n");
		return 0;
	}
	if (pwd_helper(head, cur_dir) == -1)
		return (-1);
	return (0);
}

/*
returns:
0 : no OLDPWD, no PWD
1 : yes OLDPWD, no PWD
2 : no OLDPWD, yes PWD
3 : yes OLDPWD, yes PWD
*/
int		pwd_in_env(t_node **head)
{
	int total;

	total = 0;
	if (index_in_env("test", "OLDPWD", head) >= 0)
		total += 1;
	if (index_in_env("test", "PWD", head) >= 0)
		total += 2;
	return total;
}
