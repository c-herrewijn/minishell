#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *str = "hello\n";
    int *fds;
    char buff[100];

    fds = malloc(2 * sizeof(int));
    fds[0] = 42;
    fds[1] = 21;

    printf("nr 1: %d; nr 2: %d\n", fds[0], fds[1]);


    pipe(fds);
    printf("nr 1: %d; nr 2: %d\n", fds[0], fds[1]);

    // write into the write end of the pipe
    write(fds[1], str, 6);
    close(fds[1]);

    // read from the read end of the pipe
    read(fds[0], buff, 6);
    close(fds[0]);

    printf("string from pipe: %s\n", str);
}
