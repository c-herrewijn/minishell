#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>

extern int errno ;

// executes a standard command: < infile | grep as | wc -c
int main(void)
{
	const char *grep_path = "/usr/bin/grep";
	const char *wc_path = "/usr/bin/wc";

	char *const grep_argv[] = {"grep", "as", NULL};
	char *const wc_argv[] = {"wc", "-c", NULL};
	
    extern char **environ;
	int fildes;
    int p1[2];
    pid_t new_pid;

    pipe(p1);

    // child 1
	new_pid = fork();
    if (new_pid == 0)
    {
        printf("child 1 start\n");
        fildes = open("infile", O_RDONLY);
	    dup2(fildes, STDIN_FILENO);
        close(p1[0]); // close reading end
        dup2(p1[1], STDOUT_FILENO);
	    execve(grep_path, grep_argv, environ);
        dprintf(2, "child 1 end, return code: %d\n", errno);
        exit(0); // not really needed
    }

    // child 2
	new_pid = fork();
    if (new_pid == 0)
    {
        printf("child 2 start\n");
        close(p1[1]); // close writing end

        dup2(p1[0], STDIN_FILENO);
	    execve(wc_path, wc_argv, environ);
        dprintf(2, "error child 2, return code: %d\n", errno);
        exit(0); // exit in case of error
    }

    // parent only, as all childs have exited
    close(p1[0]);
    close(p1[1]);
    wait(NULL);
    wait(NULL);
    wait(NULL); // question: why does the program still terminates with extra waits??
    wait(NULL);
    printf("new_pid: %d\n", new_pid);
    puts("finished");
}
