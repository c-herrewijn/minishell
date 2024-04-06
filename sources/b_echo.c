/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   b_echo.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 12:26:40 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/15 18:12:26 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
check if s == -n\0 or -nnnnnnnnnnnn\0
*/
static bool	is_dash_n(char *s)
{
	int	i;

	i = 1;
	if (s[0] != '-')
		return (false);
	while (s[i] != '\0')
	{
		if (s[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	b_echo(int argc, char **argv)
{
	int	i;
	int	nlflag;

	if (argc == 1)
	{
		printf("\n");
		return (0);
	}
	nlflag = true;
	i = 1;
	while (argv[i] != NULL && is_dash_n(argv[i]) == true)
	{
		nlflag = false;
		i++;
	}
	while (argv[i] != NULL)
	{
		printf("%s", argv[i]);
		if (i < argc - 1)
			printf(" ");
		i++;
	}
	if (nlflag == true)
		printf("\n");
	return (0);
}
