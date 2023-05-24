/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo_argc_argv.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 19:54:14 by kkroon        #+#    #+#                 */
/*   Updated: 2023/05/24 19:54:39 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "echoheader.h"

/*
check if s == -n\0 or -nnnnnnnnnnnn\0
*/
bool is_dash_n(char *s)
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

int main(void)
{
	char *str;
	char **arr;

	while(true)
	{
		str = readline("command : ");
		if (str == NULL)
			return 1;
		add_history(str);
		arr = ft_split(str, ' ');
		printf("|");
		b_echo(len_2d_arr(arr), arr);
		printf("|\n");
	}
	return 0;
}

/*
cc -lreadline echo_argc_argv.c echo_utils.c -o echo_test && ./echo_test
*/
