#include <unistd.h>
#include <stdio.h>

int main(void)
{
	int return_val;
	const char *path = "/usr/bin/env";
	char *const argv[] = {"env", NULL};
    extern char **environ;
    
	return_val = execve(path, argv, environ);

	// note if execve runs successfull, the process terminates, so this part won't run!
	puts("!! ERROR !!");
	printf("return val: %d\n", return_val);
}


// alternative: NOT preferred: 
// https://www.gnu.org/software/libc/manual/html_mono/libc.html#Program-Arguments
// int main (int argc, char *argv[], char *envp[])
// {
//     int return_val;
// 	const char *path = "/usr/bin/env";
// 	char *const new_argv[] = {"env", NULL};

//     return_val = execve(path, new_argv, envp);

// 	// note if execve runs successfull, the process terminates, so this part won't run!
// 	puts("!! ERROR !!");
// 	printf("return val: %d\n", return_val);
// }