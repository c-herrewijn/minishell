/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_next_line.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/30 14:34:02 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/05/11 13:44:32 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
adds data from file to store unit eof or '\n' has been found
*/
static int	read_file(int fd, char **store)
{
	int		read_len;
	char	*read_str;
	size_t	malloc_size;

	read_len = BUFFER_SIZE;
	malloc_size = 1 + ft_strlen(*store);
	while (ft_strchr(*store, '\n') == NULL && read_len == BUFFER_SIZE)
	{
		malloc_size += BUFFER_SIZE;
		read_str = malloc(malloc_size * sizeof(char));
		if (read_str == NULL)
			return (-1);
		if (*store != NULL)
			ft_strlcpy(read_str, *store, malloc_size);
		read_len = read(fd, read_str + ft_strlen(*store), BUFFER_SIZE);
		if (read_len <= 0)
		{
			free (read_str);
			return (read_len);
		}
		*(read_str + ft_strlen(*store) + read_len) = '\0';
		free (*store);
		*store = read_str;
	}
	return (read_len);
}

/*
returns the next line
removes the returned line from store
function is only called when store != NULL
*/
static char	*create_next_line(char **store)
{
	char	*next_line;
	char	*new_filepart;
	size_t	len_next_line;

	new_filepart = NULL;
	if (ft_strchr(*store, '\n') != NULL)
		len_next_line = ft_strchr(*store, '\n') - *store + 1;
	else
		len_next_line = ft_strlen(*store);
	next_line = ft_substr(*store, 0, len_next_line);
	if (next_line == NULL)
		return (NULL);
	if (len_next_line < ft_strlen(*store))
		new_filepart = ft_substr(*store, len_next_line, ft_strlen(*store));
	free(*store);
	*store = new_filepart;
	return (next_line);
}

char	*get_next_line(int fd)
{
	static char	*store = NULL;
	int			read_len;
	char		*next_line;

	read_len = 0;
	next_line = NULL;
	read_len = read_file(fd, &store);
	if (read_len < 0 && store != NULL)
	{
		free (store);
		store = NULL;
	}
	if (store != NULL)
	{
		next_line = create_next_line(&store);
		if (next_line == NULL && store != NULL)
		{
			free (store);
			store = NULL;
		}
	}
	return (next_line);
}
