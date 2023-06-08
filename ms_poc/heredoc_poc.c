#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "../libft/libft.h"

// gcc ms_poc/heredoc.c libft/libft.a

int main(int argc, char **argv, char **envp)
{
	int		my_pipe[2];
	int		res;
	char	*str1;
	char	*str2;
	char	*str_sum;
	size_t	heredoc_size;

	res = pipe(my_pipe);	// pipe to store the here document

	// get heredoc input strings
	str1 = get_next_line(STDIN_FILENO);
	str2 = get_next_line(STDIN_FILENO);

	// store both heredoc lines in a pipe, we assume there third line was the delimiter, this is not part of this POC
	res = write(my_pipe[1], str1, ft_strlen(str1));
	res = write(my_pipe[1], str2, ft_strlen(str2));

	// close writing end	
	res = close(my_pipe[1]);

	// get there heredoc (NOT null terminated) from the pipe into a string (NULL terminated)
	heredoc_size = ft_strlen(str1) + ft_strlen(str2); // NOTE: not null-terminated
	str_sum = malloc((heredoc_size + 1) * sizeof(char));  // add 1 for NULL-termination
	read(my_pipe[0], str_sum, heredoc_size);
	str_sum[heredoc_size] = '\0';

	printf("here doc (starts on next line):\n%s", str_sum);
	printf("strlen: %zu\n", ft_strlen(str_sum));

	// close reading end
	res = close(my_pipe[0]);
}
