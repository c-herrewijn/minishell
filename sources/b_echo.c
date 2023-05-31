/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   b_echo.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 12:26:40 by kkroon        #+#    #+#                 */
/*   Updated: 2023/05/31 12:29:05 by kkroon        ########   odam.nl         */
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
