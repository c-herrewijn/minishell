/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   b_cd.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 12:26:34 by kkroon        #+#    #+#                 */
/*   Updated: 2023/05/31 17:42:14 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//set env var PWD	
void	update_PWD()
{
	
}

//if cd successful and PWD is empty or unset, make OLDPWD=  empty
void	update_OLDPWD()
{
	
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
void	b_cd(char *str, t_node **head)
{
	char **cd_path;

	if (str[2] == '\0' || str[2] == ' ')
	{
		cd_path = ft_split(str, ' ');
		if (cd_path == NULL)
			return ;
		if (b_arr_len(cd_path) <= 1)
			chdir(getenv("HOME"));
		else if (cd_path[1][0] == '~' && cd_path[1][1] == '\0') // up for interpetation
			chdir(getenv("HOME"));
		else
			chdir(cd_path[1]);
		free_double_char_pointer(cd_path);
	}
}

