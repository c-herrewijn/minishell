/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   b_cd.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 12:26:34 by kkroon        #+#    #+#                 */
/*   Updated: 2023/05/31 12:28:47 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//need to update the env when cd is succesfull
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
