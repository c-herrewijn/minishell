/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 12:37:28 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/06/16 15:16:15 by cherrewi      ########   odam.nl         */
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

/*
Expander States:
- SCANNING = 'normal' parsing of characters
  - state changes to READING_VAR_NAME after $ char
  - state changes to SQUOTE_SCANNING after single quote
  - single and double quotes are stripped
  - other chars, incl. blanks are printed
- SQUOTE_SCANNING = inside single quotes
  - state changes to SCANNING after closing single quote
- READING_VAR_NAME = $ has been read
  - state changes to SCANNING after " or <blank> char
  - state changes to SQUOTE_SCANNING after single quote
  - after '\0', $, single quote, double quote, blank -> variable is expanded
  - in case the $ char is directly followed by $, blank, or '\0' -> 
      the $ char is literally printed
*/
typedef enum e_expander_state {
	SCANNING,
	SQUOTE_SCANNING,
	READING_VAR_NAME
}	t_expander_state;

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

typedef struct s_expander_data
{
	t_expander_state	state;
	size_t				i;
	size_t				var_start_index;
}	t_expander_data;

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

//update_pwd_env.c
int			update_pwd(t_node **head);

//update_oldpwd_env.c
int			update_oldpwd(t_node **head);

//b_cd.c
int			b_cd(int argc, char **argv, t_node **head);

//b_echo.c
int			b_echo(int argc, char **argv);

//b_env.c
int			b_env(t_node *head);

//b_exit.c
void		b_exit(char *exit_status);

//b_export_utils.c
bool		empty_list_add(t_node **head, char *str);
char		*remove_plus(char *str);
int			b_export_concat_inplace(char *str, t_node **head, int spot);
int			concat_helper(int argc, char **argv, t_node **head,
				char *without_plus);

//b_export.c
int			b_export_concat(int argc, char **argv, t_node **head);
int			b_export(int argc, char **argv, t_node **head);
int			execute_export(t_node **head, t_data *data, size_t i);

//b_pwd.c
int			b_pwd(void);

//b_unset.c
void		list_remove_first(t_node **head);
int			list_remove_index(t_node **head, int spot);
int			b_unset(int argc, char **argv, t_node **head);

//builtin_utils.c
void		free_double_char_pointer(char **s);
int			b_arr_len(char **s);
int			pwd_in_env(t_node **head);
t_node		*get_node_from_index(t_node **head, int index);

//index_in_env.c
int			index_in_env(char *prefix, char *str_to_find, t_node **head);

//check_for_builtin.c
int			index_of_c_in_str(char *str, char c);
int			b_export_allowed_format(int argc, char **argv);
t_builtin	check_if_builtin(char *str);

//create_env.c
int			list_len(t_node *head);
void		list_clear(t_node **head);
int			list_append(t_node **head, char *str);
int			list_create_env(t_node **head, t_data data);

//debug_printing.c
void		print_first(t_node **head);
void		print_next(t_node **head);
void		list_print(t_node *head);
void		print_env_var(char *str, t_node *head);
void		print_2d_array(char **s);
void		print_tokens(t_data *data);
char		*tokens_to_string(t_data *data);
void		print_commands(t_data *data);
void		unset_all(t_node **head);
void		debug_env_etc(char *str, t_node **head, t_data *data);

// lexer
int			lexer(t_data *data);
size_t		count_tokens(char *str);
int			create_tokens(t_data *data);
void		free_tokens(t_data *data);
bool		is_unquoted_blank(char *str, size_t i);
bool		is_unquoted_operator_char(char *str, size_t i);
bool		is_double_operator(char c1, char c2);

// parser
int			parser(t_data *data);
bool		syntax_validation(t_data *data);
bool		is_redirection_token(t_token token);
int			create_command(t_data *data, size_t command_nr);
size_t		get_start_token(t_data *data, size_t command_nr);
int			command_count_arguments(t_data *data, size_t command_nr);
void		free_commands(t_data *data);

// expander
int		expander(t_data *data);
size_t	expanded_str_len(char *in_str, t_node *env_node);
void	store_final_exit_status(t_data *data);
size_t	expander_var_len(char *in_str, t_expander_data *exp_data,
			t_node *head);
size_t	len_squote(char *in_str, t_node *env_node,
			t_expander_data *exp_data);
size_t	len_dquote(char *in_str, t_node *env_node,
			t_expander_data *exp_data);
size_t	len_dollar(char *in_str, t_node *env_node,
			t_expander_data *exp_data);
size_t	len_blank(char *in_str, t_node *env_node,
			t_expander_data *exp_data);
size_t	len_terminator(char *in_str, t_node *env_node,
			t_expander_data *exp_data);
char	*create_expanded_str(char *in_str, t_node *env_node);

// heredoc
int			add_heredoc(t_data *data, size_t command_nr);
bool		command_has_heredoc(t_data *data, size_t command_nr);

// executer.c
int			wait_for_child_processes(t_data *data);
void		run_child_process_and_exit(char **envp, t_data *data, size_t com_i);
int			execute_commands_loop(t_data *data, char **envp);
int			execute_commands(t_data *data);

// executer_commands.c
char		*combine_command_path(char *path, char *cmd);
void		execute_command_builtin(t_node **head, t_data *data, size_t i);
void		execute_command_local_dir(char **envp, char **paths,
				t_command *command);
void		execute_command_from_path(char **envp, char **paths,
				t_command *command);

// executer_pipes.c
int			create_pipes(t_data *data);
int			close_pipes_before_running_command_i(t_data *data,
				size_t i_command);
int			close_all_pipes(t_data *data);

// executer_utils.c
void		exit_child_proc_with_error(t_command *command, char **paths,
				char ***envp);
char		**get_path(char **envp);
int			create_envp_from_ll_env(t_node **head, char ***envp);
int			free_envp_return(char ***envp, int n);
void		print_child_errors(t_data *data);

//executer_redirections.c
int			apply_redirections(t_data *data, size_t i_command);

//single_builtin.c
void		execute_single_builtin(t_node **head, t_data *data);

//main_utils.c
void		free_data(t_data *data);
void		free_and_exit_with_perror(t_data *data, t_node **head);
void		init_data_struct(t_data *data, int argc, char **argv, char **envp);
int			check_data_str(t_data *data);

#endif
