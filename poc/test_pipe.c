#include <unistd.h>
#include <stdio.h>

int main(void)
{
    char *str = "hello\n";
    int fd[2];
    char buff[100];

    pipe(fd);

    // write into the write end of the pipe
    write(fd[1], str, 6);
    close(fd[1]);

    // read from the read end of the pipe
    read(fd[0], buff, 6);
    close(fd[0]);

    printf("string from pipe: %s\n", str);
}
