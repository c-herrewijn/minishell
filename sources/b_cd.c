/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   b_cd.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 12:26:34 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/09 12:32:32 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//find c in str
//is_in_env
static int	get_home_value(t_node **head, char **val)
{
	int i;
	int spot;
	char **arr;
	t_node *node;

	i = 0;
	// printf("DEBUG : START GET HOME\n");
	arr = make_is_in_env_compatible("HOME");
	if (arr == NULL)
		return -2;
	// printf("DEBUG : ARR MADE\n");
	spot = is_in_env(2, arr, head);
	// printf("DEBUG : IS IN ENV CHECKED\n");
	free(arr);
	// printf("DEBUG : ARR FREED\n");
	if (spot == -1)
	{
		// printf("DEBUG : HOME NOT FOUND\n");
		return -1;
	}
	node = *head;
	while(i < spot)
	{
		node = node->next;
		i++;
	}
	// printf("DEBUG : AFTER NODE LOOP\n");
	*val = ft_substr(node->str, ft_strlen("HOME="), ft_strlen(node->str) - ft_strlen("HOME="));
	if (*val == NULL)
		return -2;
	return 1;
}

static int	updating_pwd_oldpwd_env_vars(int ret, t_node **head)
{
	if (ret != -1)
	{
		if (update_oldpwd(head) == -1)
			return (-1);
		if (update_pwd(head) == -1)
			return (-1);
	}
	return 0;
}

//when does cd count as succesfull, kinda depends on chdir from c
//chdir returns -1 if something is incorrect with the passed path
int		b_cd(int argc, char **argv, t_node **head)
{
	int 	ret;
	char	*home_value;
	printf("DEBUG : in b_cd\n");
	ret = 0;
	if (argc == 1)
	{
		ret = get_home_value(head, &home_value);
		if (ret == -2)
			return (-1);
		// printf("DEBUG : home_value : %s\n", home_value);
		if (ret == -1)
			printf("cd : HOME not set\n");
		else
		{
			ret = chdir(home_value);
			if (ret == -1)
				printf("cd: %s: No such file or directory\n", home_value);
			free(home_value);
		}
	}
	else
	{
		ret = chdir(argv[1]);
		if (ret == -1)
			printf("cd: %s: No such file or directory\n", argv[1]);
	}
	return (updating_pwd_oldpwd_env_vars(ret, head));
}
