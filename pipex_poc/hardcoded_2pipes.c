#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>

extern int errno ;

// executes a standard command: < infile grep as | grep f | wc -c
int main(void)
{
	int return_val;
    extern char **environ;

    int fildes = open("infile", O_RDONLY);
	int res = dup2(fildes, STDIN_FILENO);
	char *const argv[] = {"cat", NULL};

	const char *grep_path = "/usr/bin/grep";
	const char *wc_path = "/usr/bin/wc";
    
	char *const grep1_argv[] = {"grep", "as", NULL};
	char *const grep2_argv[] = {"grep", "f", NULL};
	char *const wc_argv[] = {"wc", "-c", NULL};
	
    int p1[2];
    int p2[2];
    pid_t new_pid;

    pipe(p1);
    pipe(p2);
    
    // child process 1
	new_pid = fork();
    if (new_pid == 0)
    {
        dup2(fildes, STDIN_FILENO); // read from intput file
        dup2(p1[1], STDOUT_FILENO); // write to first pipe

        close(p1[0]); // close other sides of the pipes
        close(p2[0]); 
        close(p2[1]); 

        dprintf(2, "child 1 start\n");
	    execve(grep_path, grep1_argv, environ);
        dprintf(2, "child 1 end, return code: %d\n", errno);
        exit(0); // exit in case of error
    }

    // child process 2
	new_pid = fork();
    if (new_pid == 0)
    {
        dup2(p1[0], STDIN_FILENO); // read from first pipe
        dup2(p2[1], STDOUT_FILENO); // write to second pipe

        close(p1[1]); // close other sides of the pipes
        close(p2[0]); 

        dprintf(2, "child 2 start\n");
	    execve(grep_path, grep2_argv, environ);
        dprintf(2, "child 2 end, return code: %d\n", errno);
        exit(0); // exit in case of error
    }

    // child process 3
	new_pid = fork();
    if (new_pid == 0)
    {
        dup2(p2[0], STDIN_FILENO); // read from first pipe
        // note STDOUT_FILENO is unchanged, so still points to the terminal

        close(p1[0]); // close other sides of the pipes
        close(p1[1]);
        close(p2[1]); 

        dprintf(2, "child 3 start\n");
	    execve(wc_path, wc_argv, environ);
        dprintf(2, "child 3 end, return code: %d\n", errno);
        exit(0); // exit in case of error
    }

    // parent only, as all childs have exited
    close(p1[0]);
    close(p1[1]);
    close(p2[0]);
    close(p2[1]);
    wait(NULL);
    wait(NULL);
    wait(NULL);
    puts("finished");
}