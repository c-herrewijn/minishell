#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

char *taking_input(char *str)
{
	while(true)
	{
		str = readline("input: ");
		if (str == NULL)
			break;
		add_history(str);
		printf("%s\n", str);
	}
}

int main(int argc, char **argv, char **envp)
{
	char *str;

	str = taking_input(str);
	return 0;
}

/*
cc -lreadline *.c
./a.out
*/