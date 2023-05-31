/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   b_pwd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 12:26:53 by kkroon        #+#    #+#                 */
/*   Updated: 2023/05/31 12:28:54 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//not sure which edgecases pwd would need
//or if pwd makes changes elsewhere, should not be
void	b_pwd(void)
{
	char	s[PATH_MAX];

	getcwd(s, sizeof(s));
	printf("%s\n", s);
}
