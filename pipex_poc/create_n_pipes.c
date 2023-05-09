#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


static void	create_pipes(int (**pipes)[2], int nr_pipes)
{
	int i;
	int result;
	
	*pipes = malloc(nr_pipes * 2 * sizeof(int));
	
	i = 0;
	while (i < nr_pipes)
	{
		result = pipe((*pipes)[i]);
		if (result < 0)
		{
			free(*pipes);
			*pipes = NULL;
		}
		i++;
	}
}

int main(void)
{
	int (*pipes)[2];

	create_pipes(&pipes, 3);

	printf("%d\n", pipes[0][0]);
	printf("%d\n", pipes[0][1]);
	printf("%d\n", pipes[1][0]);
	printf("%d\n", pipes[1][1]);
	printf("%d\n", pipes[2][0]);
	printf("%d\n", pipes[2][1]);
}
