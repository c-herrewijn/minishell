#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


void reroute(fd)
{
	dup2(fd, STDOUT_FILENO);
}

int main(void)
{
	int	fd_out1;
	int	fd_out2;

	fd_out1 = open("outfile_1", O_TRUNC | O_CREAT | O_WRONLY, 0644);  // creates outfile_1
	fd_out2 = open("outfile_2", O_TRUNC | O_CREAT | O_WRONLY, 0644);  // creates outfile_2

	puts("first line");  // terminal output
	
	dup2(fd_out1, STDOUT_FILENO);
	puts("second line");  // output in outfile_1
	
	reroute(fd_out2);  // reroute happens in other function, but has global impact since it changes the file descriptor table.
	puts("third line");  // output in outfile_2
}
