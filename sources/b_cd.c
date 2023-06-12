/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   b_cd.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 12:26:34 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/12 15:59:43 by kkroon        ########   odam.nl         */
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

	h_len = ft_strlen("HOME=");
	i = 0;
	spot = index_in_env("test", "HOME", head);
	if (spot == -1)
	{
		// printf("DEBUG : HOME NOT FOUND\n");
		return (-1);
	}
	node = *head;
	while (i < spot)
	{
		node = node->next;
		i++;
	}
	*val = ft_substr(node->str, h_len, ft_strlen(node->str) - h_len);
	if (*val == NULL)
		return (-2);
	return (1);
}

static int	change_dir(int argc, char **argv, t_node **head, int *ret)
{
	char	*home_value;

	if (argc == 1)
	{
		*ret = get_home_value(head, &home_value);
		if (*ret == -2)
			return (-1);
		if (*ret == -1)
			printf("cd : HOME not set\n");
		else
		{
			*ret = chdir(home_value);
			if (*ret == -1)
				printf("cd: %s: No such file or directory\n", home_value);
			free(home_value);
		}
	}
	else
	{
		*ret = chdir(argv[1]);
		if (*ret == -1)
			printf("cd: %s: No such file or directory\n", argv[1]);
	}
	return (0);
}

//when does cd count as succesfull, kinda depends on chdir from c
//chdir returns -1 if something is incorrect with the passed path
int	b_cd(int argc, char **argv, t_node **head)
{
	int	ret;

	ret = 0;
	if (change_dir(argc, argv, head, &ret) == -1)
		return (-1);
	if (ret != -1)
	{
		if (update_oldpwd(head) == -1)
			return (-1);
		if (update_pwd(head) == -1)
			return (-1);
	}
	return (0);
}
