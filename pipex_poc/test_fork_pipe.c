#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
	int p1[2];
	char read_buff[100];
	pid_t new_pid;

	pipe(p1);
	new_pid = fork();
	if (new_pid != 0)
	{
		close(p1[1]); // close writing end
		puts("parent waiting for child:");
		wait(NULL);
		puts("parent reading from pipe");
		read(p1[0], read_buff, 7);
		printf("transmission received: %s\n", read_buff);
		puts("parent finised");
		close(p1[0]); // close reading end
	}
	else
	{
		close(p1[0]); // close reading end
		puts("child speaking into the pipe");
		write(p1[1], "hallo\n\0", 7);
		close(p1[1]); // close writing end
	}
	return 1;
}
