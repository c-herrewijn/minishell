/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   b_cd.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 12:26:34 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/02 19:25:41 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//when does cd count as succesfull, kinda depends on chdir from c
//chdir returns -1 if something is incorrect with the passed path
int		b_cd(char *str, t_node **head)
{
	char **cd_path;
	int ret;
	
	ret = 0;
	if (str[2] == '\0' || str[2] == ' ')
	{
		cd_path = ft_split(str, ' ');
		if (cd_path == NULL)
			return -1;
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
		if (update_oldpwd(head) == -1)
			return (-1);
		if (update_pwd(head) == -1)
			return (-1);
	}
	return 0;
}
