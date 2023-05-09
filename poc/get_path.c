#include <stdio.h>
#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		result;

	i = 0;
	result = 0;
	while ((result == 0) && (i < n))
	{
		result = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (s1[i] == '\0' || s2[i] == '\0')
			break ;
		i++;
	}
	return (result);
}

int main(int argc, char *argv[], char **envp)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break;
		i++;
	}
	puts("Path:");
	printf("%s\n", envp[i]);
	puts("Stripped Path:");
	printf("%s\n", envp[i] + 5);
}