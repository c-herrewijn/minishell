#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
    printf("size of descriptor table: %d\n", getdtablesize());
    
    int new_fd = dup(STDOUT_FILENO);
    // new_fd now also points to the terminal, because it is a copy of STDOUT_FILENO 
    write(new_fd, "test write to new fd\n", 21);
    printf("new_fd: %d\n", new_fd);

    // normally prints to terminal via standard out 
    printf("stdin %d\n", STDIN_FILENO);    // 0
    printf("stdout %d\n", STDOUT_FILENO);  // 1
    printf("stderr %d\n", STDERR_FILENO);  // 2

    int fildes = open("test.txt", O_WRONLY);

    // redirect standard out to new fd
    int res = dup2(fildes, STDOUT_FILENO);

    // printf still prints to standard out, but standard out now points to the file.
    printf("stdout %d\n", STDOUT_FILENO);  // 1
    printf("hello\n"); 
    printf("res: %d\n", res); 
}
