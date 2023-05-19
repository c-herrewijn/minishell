/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo_cd_pwd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 22:35:03 by kkroon        #+#    #+#                 */
/*   Updated: 2023/05/19 22:39:06 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//works with -n (no newline) flag
void	b_echo(char *str)
{
	int len;
	int nlflag;
	int i;

	i = 5;
	nlflag = true;
	len = (int)ft_strlen(str);
	if (len <= 5)
		return ;
	if (len >= 7)
	{
		if (str[5] == '-' && str[6] == 'n')
		{
			nlflag = false;
			i = 7;
		}	
	}
	printf("%s", str + i);
	if (nlflag == true)
		printf("\n");
}

//need to update the env when cd is succesfull
void	b_cd(char *str, t_node **head)
{
	char **cd_path;
	cd_path = ft_split(str, ' ');

	if (b_arr_len(cd_path) <= 1)
		chdir(getenv("HOME"));
	else if (cd_path[1][0] == '~' && cd_path[1][1] == '\0') // up for interpetation
		chdir(getenv("HOME"));
	else
		chdir(cd_path[1]);
}

//not sure which edgecases pwd would need
//or if pwd makes changes elsewhere, should not be
void	b_pwd(void)
{
	char	s[PATH_MAX];

	getcwd(s, sizeof(s));
	printf("%s\n", s);
}
