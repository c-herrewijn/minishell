#include <unistd.h>
#include <stdio.h>

int main(void)
{
	int res;

	res = dup2(100, 101);
	printf("res: %d\n", res);
	perror(NULL);
}
