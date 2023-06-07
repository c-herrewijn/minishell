/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   b_cd.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 12:26:34 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/07 16:50:16 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//when does cd count as succesfull, kinda depends on chdir from c
//chdir returns -1 if something is incorrect with the passed path
int		b_cd(int argc, char **argv, t_node **head)
{
	int ret;

	printf("DEBUG : in b_cd\n");
	ret = 0;
	if (argc == 1)
		ret = chdir(getenv("HOME"));
	else if (argv[1][0] == '~' && argv[1][1] == '\0') // up for interpetation
		ret = chdir(getenv("HOME"));
	else
		ret = chdir(argv[1]);
	if (ret != -1)
	{
		if (update_oldpwd(head) == -1)
			return (-1);
		if (update_pwd(head) == -1)
			return (-1);
	}
	return 0;
}
//need to double check if using getenv