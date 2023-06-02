/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_pwd_env.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 22:13:45 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/02 19:34:04 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	oldpwd_helper(t_node **head)
{
	int		pwdspot;
	int		oldpwdspot;
	t_node	*pwdnode;
	t_node	*oldpwdnode;
	int		i;

	pwdnode = *head;
	oldpwdnode = *head;
	pwdspot = is_in_env("export PWD", head, 2);
	oldpwdspot = is_in_env("export OLDPWD", head, 2);
	i = 0;
	while (pwdnode->next != NULL && i < pwdspot)
	{
		pwdnode = pwdnode->next;
		i++;
	}
	i = 0;
	while (oldpwdnode->next != NULL && i < oldpwdspot)
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

static int	pwd_helper(t_node **head, char *cur_dir)
{
	t_node	*node;
	int		i;
	int		spot;
	
	node = *head;
	spot = is_in_env("export PWD", head, 2);
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
	if (is_in_env("export OLDPWD", head, 2) >= 0)
		total += 1;
	if (is_in_env("export PWD", head, 2) >= 0)
		total += 2;
	return total;
}
