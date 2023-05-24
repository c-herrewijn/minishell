/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echoheader.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 19:54:28 by kkroon        #+#    #+#                 */
/*   Updated: 2023/05/24 19:54:31 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

int					len_2d_arr(char **arr);
void				free_2d_arr(char **arr);
size_t				ft_strlen(const char *s);
void				*ft_calloc(size_t count, size_t size);
static size_t		count_words(char const *s, char c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
static size_t		word_len(char const *s, char c);
static void			free_arr(char **arr);
static char const	*st_wrd(char const *s, char c, char **arr, size_t i_w);
char				**ft_split(char const *s, char c);

#endif
