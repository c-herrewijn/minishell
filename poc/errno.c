#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv)
{
	extern int errno ;
	int res;

	res = open("infile", O_RDONLY);
	printf("open result: %d\n", res);
	printf("errno: %d\n", errno);

	perror(NULL);

	// in terminal, use 'echo $?' to view exit code
}
