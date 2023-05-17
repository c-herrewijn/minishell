#include "../sources/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char *str;
	str = malloc(100);
	printf("%p\n", str);
	// char *getcwd(char *buf, size_t size);
	// size doesnt seem to matter in the sense of getting the right pwd string
	// unless size is <= 0
	// getcwd(str, 1);
	str = getcwd(str, 100);
	printf("%p\n", str);
	// it seems like getcwd allocated, judging from the source code
	printf("str : %s\n", str); // str : /Users/kkroon/codam/minishell/ms_poc
	free(str);
	// free(str);

	//PATH_MAX is from syslimits.h, which is included in other headers
	//value is 1024 meaning space for 1024 bytes
	char str2[PATH_MAX];
	// works without assigning return aswell
	getcwd(str2, sizeof(str2));
	printf("str2 : %s\n", str2); // str2 : /Users/kkroon/codam/minishell/ms_poc
	// free(str2);
	char *str3;
	getcwd(str3, 1);
	printf("str3 : %s\n", str3); // (null)

	char *str4;
	str4 = getcwd(NULL, 0);
	printf("str4 : %s\n", str4); // /Users/kkroon/codam/minishell/ms_poc
	free(str4);
}

/*
cc getcwd.c -o getcwd
./getcwd
*/
