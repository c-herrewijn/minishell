/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   b_echo.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 12:26:40 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/03 19:45:29 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
check if s == -n\0 or -nnnnnnnnnnnn\0
*/
static bool is_dash_n(char *s)
{
	int i;
	int len;

	i = 1;
	len = (int) ft_strlen(s);
	if (s[0] != '-')
		return false;
	while (s[i] != '\0')
	{
		if (s[i] != 'n')
			return false;
		i++;
	}
	return true;
}

void	b_echo(int argc, char **argv)
{
	int i;
	int nlflag;

	printf("DEBUG : in b_echo\n");
	if (argc == 1)
	{
		printf("\n");
		return ;
	}
	nlflag = true;
	i = 1;
	while(argv[i] != NULL && is_dash_n(argv[i]) == true)
	{
		nlflag = false;
		i++;
	}
	while(argv[i] != NULL)
	{
		printf("%s", argv[i]);
		if (i < argc - 1)
			printf(" ");
		i++;
	}
	if (nlflag == true)
		printf("\n");
}
