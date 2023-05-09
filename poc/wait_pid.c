#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>


// executes a c executable
int main(void)
{
	const char	*path = "exit42.out";
	char *const	argv[] = {"exit42.out", NULL};
	extern char	**environ;
	int			return_val;
	pid_t		new_pid;
	pid_t		return_pid;
	int			stat_loc;

	// int WIFEXITED(int status);

	new_pid = fork();
	if (new_pid == 0)
	{
		// child process
		return_val = execve(path, argv, environ);
		// note if execve runs successfull, the process terminates, so this part won't run!
		puts("!! ERROR !!");
		printf("return val: %d\n", return_val);
		exit(1);
	}

	// parent process
	return_pid = waitpid(new_pid, &stat_loc, 0);
	if WIFEXITED(stat_loc)
	{
		printf("exit status from sub process: %d\n", WEXITSTATUS(stat_loc));
		exit(WEXITSTATUS(stat_loc));
	}
	else
	{
		puts("sub process did not end");
		exit(1);
	}
}
