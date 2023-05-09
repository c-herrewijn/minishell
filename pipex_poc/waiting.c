#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
	int id;

	wait(NULL); // process does NOT wait, because it knows there is no child.
	
	puts("start waiting");
	id = fork();
	if (id != 0)
	{
		// parent
		// waitpid(id, NULL, 0);
		wait(NULL);  // waiting for the child to finish
	}
	if (id == 0)
	{
		// child
		while (1)
		; // infinite loop
	}
	puts("finished waiting");
}
