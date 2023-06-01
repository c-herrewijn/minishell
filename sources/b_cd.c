/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   b_cd.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 12:26:34 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/01 21:10:50 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//very similiar situation to b_export_concat_inplace
//double check the deal with total
//just ft_strjoin "OLD" and node->str of PWD
void	update_OLDPWD(t_node **head)
{
	int total;
	int pwdspot;
	int oldpwdspot;
	char 	*str;
	t_node	*pwdnode;
	t_node	*oldpwdnode;
	int		i;

	total = pwd_in_env(head);
	if (total <= 2)
	{
		printf("DEBUG : no PWD or OLDPWD present in env : total = %d\n", total);
		return ;
	}
	if (*head == NULL) // is this really needed or should catch somewhere more central, like check_for_builtin
	{
		printf("*head == NULL it seems\n");
		return ;
	}
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
	str = ft_strjoin("OLD", pwdnode->str);
	free(oldpwdnode->str);
	oldpwdnode->str = str;
	return;
}

//set env var PWD
//store return of getcwd
//very similiar situation to b_export_concat_inplace
/*
create a new string with name=getcwdreturn
loop until spot in linked list when PWD is
free(node->str)
node->str = name=getcwdreturn
prob want to use ft_strjoin
*/
void	update_PWD(t_node **head)
{
	int		total;
	char	cur_dir[PATH_MAX];
	char 	*str;
	t_node	*node;
	int		i;
	int		spot;

	total = pwd_in_env(head);
	if (total == 0 || total == 1)
	{
		printf("DEBUG : no PWD present in env : total = %d\n", total);
		return ;
	}
	if (*head == NULL) // is this really needed or should catch somewhere more central, like check_for_builtin
	{
		printf("*head == NULL it seems\n");
		return ;
	}
	node = *head;
	if (getcwd(cur_dir, sizeof(cur_dir)) == NULL)
	{
		printf("ERROR : getcwd fail\n");
		return ;
	}
	spot = is_in_env("export PWD", head, 2);
	i = 0;
	while (node->next != NULL && i < spot)
	{
		node = node->next;
		i++;
	}
	str = ft_strjoin("PWD=", cur_dir);
	free(node->str);
	node->str = str;
	return ;
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

//when does cd count as succesfull, kinda depends on chdir from c
//chdir returns -1 if something is incorrect with the passed path
void	b_cd(char *str, t_node **head)
{
	char **cd_path;
	int ret;
	
	ret = 0;
	if (str[2] == '\0' || str[2] == ' ')
	{
		cd_path = ft_split(str, ' ');
		if (cd_path == NULL)
			return ;
		if (b_arr_len(cd_path) <= 1)
			ret = chdir(getenv("HOME"));
		else if (cd_path[1][0] == '~' && cd_path[1][1] == '\0') // up for interpetation
			ret = chdir(getenv("HOME"));
		else
			ret = chdir(cd_path[1]);
		free_double_char_pointer(cd_path);
	}
	if (ret != -1)
	{
		update_OLDPWD(head);
		update_PWD(head);
	}
}
