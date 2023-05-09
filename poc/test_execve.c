#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

extern int errno ;

// -------------------------------------
// executes a .sh file
// int main(void)
// {
//     int return_val;
//     const char *path = "./test.sh";

//     puts("aa");
//     return_val = execve(path, NULL, NULL);

//     // note if execve runs successfull, the process terminates, so this part won't run!
//     printf("return val: %d\n", return_val);
//     puts("bb");    
// }

// -------------------------------------

// executes a standard command
// int main(void)
// {
// 	int return_val;
// 	const char *path = "/bin/ls";
// 	char *const argv[] = {"ls", NULL};
// 	extern char **environ;

// 	return_val = execve(path, argv, environ);
	
// 	// note if execve runs successfull, the process terminates, so this part won't run!
// 	puts("!! ERROR !!");
// 	printf("return val: %d\n", return_val);
// }

// executes a standard command
int main(void)
{
	int return_val;

    int fildes = open("infile", O_RDONLY);
	int res = dup2(fildes, STDIN_FILENO);

	const char *path = "/usr/bin/wc";
	char *const argv[] = {"wc", "-c", NULL};
	extern char **environ;

	return_val = execve(path, argv, environ);
	
	// note if execve runs successfull, the process terminates, so this part won't run!
	puts("!! ERROR !!");
	printf("errno: %d\n", errno);
	printf("return val: %d\n", return_val);
}

// -------------------------------------

// executes a c executable
// int main(void)
// {
// 	int return_val;
// 	const char *path = "hello_world.out";
// 	char *const argv[] = {"hello_world.out", NULL};
// 	extern char **environ;

// 	return_val = execve(path, argv, environ);
	
// 	// note if execve runs successfull, the process terminates, so this part won't run!
// 	puts("!! ERROR !!");
// 	printf("return val: %d\n", return_val);
// }

// -------------------------------------
