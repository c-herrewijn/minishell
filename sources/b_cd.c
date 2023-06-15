/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   b_cd.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 12:26:34 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/15 15:06:03 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//use index_in_env
static int	get_home_value(t_node **head, char **val)
{
	int		i;
	int		spot;
	t_node	*node;
	size_t	h_len;

	*val = NULL;
	h_len = ft_strlen("HOME=");
	i = 0;
	spot = index_in_env("nil", "HOME", head);
	if (spot == -1)
		return (1);
	node = *head;
	while (i < spot)
	{
		node = node->next;
		i++;
	}
	*val = ft_substr(node->str, h_len, ft_strlen(node->str) - h_len);
	if (*val == NULL)
		return (-1);
	return (0);
}

static int	cdir_argc_one(t_node **head, int *ret)
{
	char	*home_value;

	*ret = get_home_value(head, &home_value);
	if (*ret == -1)
		return (-1);
	if (*ret == 1)
	{
		if (write(2, "cd: HOME not set\n", 17) == -1)
			return (-1);
		return (1);
	}
	*ret = chdir(home_value);
	free(home_value);
	if (*ret == -1)
	{
		perror("cd");
		return (1);			
	}
	return 0;
}

static int	change_dir(int argc, char **argv, t_node **head, int *ret)
{
	int cdir_ret;
	cdir_ret = 0;
	if (argc == 1)
	{
		cdir_ret = cdir_argc_one(head, ret);
		if (cdir_ret != 0)
			return (cdir_ret);
	}
	else
	{
		*ret = chdir(argv[1]);
		if (*ret == -1)
		{
			perror("cd");
			return (1);
		}
	}
	return (0);
}

//when does cd count as succesfull, kinda depends on chdir from c
//chdir returns -1 if something is incorrect with the passed path
int	b_cd(int argc, char **argv, t_node **head)
{
	int	ret;
	int cdir;
	
	ret = 0;
	cdir = change_dir(argc, argv, head, &ret);
	if (cdir != 0)
		return (cdir);
	if (ret != -1)
	{
		if (update_oldpwd(head) == -1)
			return (-1);
		if (update_pwd(head) == -1)
			return (-1);
	}
	return (0);
}
