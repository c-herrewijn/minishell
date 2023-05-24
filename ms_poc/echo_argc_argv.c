#include "echoheader.h"

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
	if (argv[1][0] == '-' && argv[1][1] == 'n' && argv[1][2] == '\0')
	{
		nlflag = false;
		i = 2;
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

int main2(int argc, char **argv)
{
	b_echo(argc, argv);
	return 0;
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
		main2(len_2d_arr(arr), arr);
		printf("|\n");
	}
	return 0;
}

/*
cc -lreadline echo_argc_argv.c echo_utils.c -o echo_test && ./echo_test
*/
