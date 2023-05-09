#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    int outfile = open("outfile", O_TRUNC | O_CREAT | O_WRONLY, 0644);
    int res;
    
    res = dup2(outfile, STDOUT_FILENO);
    puts("text written to file:");
    write(1, "hallo\n", 6);
    printf("hallo again");
}
