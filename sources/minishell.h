/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 12:37:28 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/08 14:07:02 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
}	t_data;

//update_pwd_env.c
int		update_oldpwd(t_node **head);
int		update_pwd(t_node **head);
int		pwd_in_env(t_node **head);

//b_cd.c
int		b_cd(int argc, char **argv, t_node **head);

//b_echo.c
void	b_echo(int argc, char **argv);

//b_env.c
void	b_env(t_node *head);

//b_exit.c
void	b_exit(char *exit_status);

//b_export_utils.c
bool	empty_list_add(t_node **head, char *str);
char	*remove_plus(char *str);
int		b_export_concat_inplace(char *str, t_node **head, int spot);
int		concat_helper(int argc, char **argv, t_node **head, char *without_plus);

//b_export.c
int		b_export_concat(int argc, char **argv, t_node **head);
int		b_export(int argc, char **argv, t_node **head);

//b_pwd.c
void	b_pwd(void);

//builtin_utils.c
int		is_in_env(int argc, char **argv, t_node **head);
void	free_double_char_pointer(char **s);
int		b_arr_len(char **s);
char	**make_is_in_env_compatible(char *str);

//builtin_unset.c
void	unset_all(t_node **head);
void	list_remove_first(t_node **head);
void	list_remove_index(t_node **head, int spot);
void	b_unset(int argc, char **argv, t_node **head);

//check_for_builtin.c
int			index_of_c_in_str(char *str, char c);
int			b_export_allowed_format(int argc, char **argv);
t_builtin	check_if_builtin(char *str);
int			old_builtin_test(char *str, t_node **head, t_data *data);

//create_env.c
int		list_len(t_node *head);
void	list_clear(t_node **head);
int		list_append(t_node **head, char *str);
int		list_create_env(t_node **head, t_data data);

//debug_printing.c
void	print_first(t_node **head);
void	print_next(t_node **head);
void	list_print(t_node *head);
void	print_env_var(char *str, t_node *head);
void	print_2d_array(char **s);
void	print_tokens(t_data *data);
char	*tokens_to_string(t_data *data);
void	print_commands(t_data *data);
void	debug_env_etc(char *str, t_node **head, t_data *data);

// lexer
int		lexer(t_data *data);
size_t	count_tokens(char *str);
int		create_tokens(t_data *data);
void	free_tokens(t_data *data);
bool	is_unquoted_blank(char *str, size_t i);
bool	is_unquoted_operator_char(char *str, size_t i);
bool	is_double_operator(char c1, char c2);

// parser
int		parser(t_data *data);
bool	syntax_validation(t_data *data);
bool	is_redirection_token(t_token token);
int		create_command(t_data *data, size_t command_nr);
size_t	get_start_token(t_data *data, size_t command_nr);
int		command_count_arguments(t_data *data, size_t command_nr);
void	free_commands(t_data *data);

// heredoc
int		add_heredoc(t_data *data, size_t command_nr);

// executer
int		execute_commands(t_data *data);
int		apply_redirections(t_data *data, size_t i_command);

#endif
