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

// rl functions
// readline, rl_clear_history, rl_on_new_line,
// rl_replace_line, rl_redisplay, add_history,

int main(int argc, char **argv, char **envp)
{
	char *str;

	while(1)
	{
		str = readline("input: ");
		if (str == NULL)
			break;
		add_history(str);
		printf("%s\n", str);
	}
	return 0;
}

/*
cc -lreadline rl_functions.c -o rl_functions
./rl_functions
end with ctrl-c
*/