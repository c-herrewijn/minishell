// compile:
// gcc ms_poc/expander_poc.c ./libft/libft.a


# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>
# include <limits.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <termios.h>
# include <curses.h>
# include <term.h>

typedef enum e_lexer_state {
	DELIMITED,
	READING_WORD,
	READING_OPERATOR
}	t_lexer_state;

typedef enum e_token_type {
	WORD,
	PIPE,
	REDIRECT_INPUT,
	HEREDOC,
	REDIRECT_OUTPUT,
	REDIRECT_OUTPUT_APPEND,
}	t_token_type;

typedef enum e_builtin
{
	NOT_BUILTIN,
	B_CD,
	B_ECHO,
	B_PWD,
	B_EXPORT,
	B_UNSET,
	B_ENV,
	B_EXIT
}	t_builtin;

typedef struct s_node
{
	char			*str;
	struct s_node	*next;
}	t_node;

typedef struct s_token
{
	t_token_type	type;
	char			*word;
}	t_token;

typedef struct s_redirection
{
	t_token_type	redirection_type;
	char			*word;
}	t_redirection;

/*
simple command as described by the shell grammar
https://www.man7.org/linux/man-pages/man1/bash.1.html#SHELL_GRAMMAR
*/
typedef struct s_command
{
	int				argc;
	char			**argv;
	t_node			*envp;
	t_redirection	**redirections;
	char			*executable_location;
	pid_t			pid;
	int				exit_status;
	int				heredoc_pipe[2];
}	t_command;

typedef struct s_data
{
	int			argc;
	char		**argv;
	char		**envp;
	char		*str;
	size_t		nr_tokens;
	t_token		*token_arr;
	size_t		nr_commands;
	t_command	*command_arr;
	size_t		nr_pipes;
	int			(*pipes)[2];
	char		**paths;
	t_node		*head;
	int			previous_exit_status;
}	t_data;

int index_of_c_in_str(char *str, char c)
{
	int i;

	i = 0;
	if (str == NULL || c == 0)
		return -1;
	while(str[i] != '\0')
	{
		if (str[i] == c)
			return i;
		i++;
	}
	return -1;
}

//s1 = argv[1]
//s2 = node->str
//loop until '=' sign in argv[1] if argv is export name=value
//else loop through entire argv[1] and at the end check if next character is a '='
static bool		special_strcmp(char *s1, char *s2, int flag)
{
	int i;
	int equals;
	
	i = 0;
	equals = (int)ft_strlen(s1);
	if (flag == 0)
		equals = index_of_c_in_str(s1, '=');	
	while(s2[i] != '\0' && i < equals)
	{
		if (s1[i] != s2[i])
			return false;
		i++;
	}
	if (s2[i] == '=')
		return true;
	return false;
}

// get length of double char pointer
int		b_arr_len(char **s)
{
	int i;

	i = 0;
	while(s[i] != NULL)
	{
		i++;
	}
	return i;
}

// add to the end
// helper to list_create_env
// also used in b_export
// flag is just for debugging, need to remove later and update in minishell.h
int list_append(t_node **head, char *str)
{
	t_node *node;

	node = *head;
	while(node->next != NULL)
		node = node->next;
	node->next = malloc(sizeof(t_node));
	node->next->str = NULL;
	if (node->next == NULL)
		return (-1);
	node->next->str = str;
	node->next->next = NULL;
	return (0);
}

// main func, called from main
// NOTE: adjusted by CH
int list_create_env(t_node **head, char **env_arr)
{
	int i;
	char *cpy;
	int envplen;

	i = 1;
	envplen = b_arr_len(env_arr);
	if (envplen == 0)
		return (0);
	cpy = ft_substr(env_arr[0], 0, ft_strlen(env_arr[0]));
	if (cpy == NULL)
		return (-1);
	*head = malloc(sizeof(t_node));
	if ((*head) == NULL)
	{
		free(cpy);
		return (-1);
	}
	(*head)->str = cpy;
	(*head)->next = NULL;
	while(env_arr[i] != NULL)
	{
		cpy = ft_substr(env_arr[i], 0, ft_strlen(env_arr[i]));
		if (list_append(head, cpy) == -1)
			return (-1);
		i++;
	}
	return (0);
}


// new functions start here
// ---------------------------------------------------------


// returns the index of the variable name, or -1 if not found
// a return >= 0 means str is an environment variable
int	find_str_in_environment(t_node *env, char *str)
{
	int	i;

	i = 0;
	while(env != NULL)
	{
		if (ft_strncmp(str, env->str, ft_strlen(str)) == 0)
			return (i);
		i++;
		env = env->next;
	}
	return (-1);
}

// work in progress:


int main(int argc, char **argv, char **envp)
{
	t_node *env_llist;
	int		env_index;

	list_create_env(&env_llist, envp);

	printf("first env_llist %s\n", env_llist->str);

	env_index = find_str_in_environment(env_llist, "HOME");
	printf("env_index: %d\n", env_index);
	env_index = find_str_in_environment(env_llist, "TERM_PROGRAM");
	printf("env_index: %d\n", env_index);
	env_index = find_str_in_environment(env_llist, "SHELL");
	printf("env_index: %d\n", env_index);
	env_index = find_str_in_environment(env_llist, "HOMEAAA");
	printf("env_index: %d\n", env_index);
}

