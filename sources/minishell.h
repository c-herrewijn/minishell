/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 12:37:28 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/05/19 22:46:53 by kkroon        ########   odam.nl         */
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

/*
probally handy to keep a copy of the params of main
i think its bad practice to use the params from main directly

also think its handy to keep track of input str from readline in this
*/
typedef struct s_data
{
	int		argc;
	char	**argv;
	char	**envp;
	char	*str;
}	t_data;

/*
using this instead of t_list
because then i dont need to type cast all the time the void *content

might convert all functions to use t_list later and will remove this then
*/
typedef struct s_node
{
	char			*str;
	struct s_node	*next;
}	t_node;

//builtin_unset.c
void	list_remove_first(t_node **head);
void	list_remove_index(t_node **head, int spot);
void	b_unset(char *str, t_node **head);

//check_for_builtin.c
int		b_arr_len(char **s);
void	check_if_builtin(char *str, t_node **head);

//create_env.c
void list_clear(t_node *head);
void list_append(t_node **head, char *str);
void list_create_env(t_node **head, t_data data);

//debug_printing.c
void	list_print(t_node *head);
void	print_env_var(char *str, t_node *head);
void	print_2d_array(char **s);

/*
probally will split these two files up more later
*/

//echo_cd_pwd.c
void	b_echo(char *str);
void	b_cd(char *str, t_node **head);
void	b_pwd(void);

//export_env_exit.c
void	b_export(char *str, t_node **head);
void	b_env(char *str, t_node **head);
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
