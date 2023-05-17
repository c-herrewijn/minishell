/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 12:37:28 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/05/17 22:45:43 by kkroon        ########   odam.nl         */
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

typedef struct s_token
{
	char		type;
	char		*word;
	char		operator[2];
}	t_token;

typedef enum e_lexer_state {
	DELIMITED = 0,
	READING_WORD = 1,
	READING_OPERATOR = 2
}	t_lexer_state;

typedef struct s_data
{
	int		argc;
	char	**argv;
	char	**envp;
	char	**envp_copy;
	char	*str;
}	t_data;

/*
b_
builtin functions remake
builtins.c
*/
void	b_free_arr(char **s);
int		b_arr_len(char **s);
void	check_if_builtin(char *str, char **envp);
void	b_echo(char *str);
void	b_cd(char *str, char **envp);
void	b_pwd(void);
void	b_export(void);
void	b_unset(void);
void	b_env(void);
void	b_exit(void);

// lexer
size_t	count_tokens(char *str);
void	count_tokens_delimited(size_t *word_count, t_lexer_state *state,
			char *str, size_t index);
void	count_tokens_reading_operator(size_t *word_count, t_lexer_state *state,
			char *str, size_t index);
void	count_tokens_reading_word(size_t *word_count, t_lexer_state *state,
			char *str, size_t index);
bool	is_unquoted_blank(char *str, size_t i);
bool	is_unquoted_operator_char(char *str, size_t i);
bool	is_double_operator(char c1, char c2);

#endif
