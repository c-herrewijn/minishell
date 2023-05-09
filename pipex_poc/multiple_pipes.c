#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    int	(*pipes)[2];
    int nr_pipes = 4;

    printf("size one pipe: %lu\n", sizeof(pipes[0]));

    // store 4 pipes
    pipes = malloc(nr_pipes * 2 * sizeof(int));
    pipe(pipes[0]);
    pipe(pipes[1]);
    pipe(pipes[2]);
    pipe(pipes[3]);

    printf("pipes[3][0]: %d\n", pipes[3][0]);
}