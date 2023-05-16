/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 15:12:01 by cherrewi      #+#    #+#                 */
/*   Updated: 2022/10/23 13:59:48 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
counts the number of words between the delimiters
multiple consequtive delimiters are interpreted as 1
*/
static size_t	count_words(char const *s, char c)
{
	size_t	nr_words;

	if (*s && !c)
		return (1);
	nr_words = 0;
	while (*s)
	{
		if (*s != c && *s)
		{
			nr_words++;
			while (*s != c && *s)
				s++;
		}
		while (*s == c)
			s++;
	}
	return (nr_words);
}

/*
finds length of word to next delimiter
*/
static size_t	word_len(char const *s, char c)
{
	size_t	word_len;

	word_len = 0;
	while (*s != c && *s != '\0')
	{
		word_len++;
		s++;
	}
	return (word_len);
}

/*
frees the array
to be used in case the malloc fails
*/
static void	free_arr(char **arr)
{
	int	i;

	if (arr != NULL)
	{
		i = 0;
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

/*
saves the word in the array
*/
static char const	*st_wrd(char const *s, char c, char **arr, size_t i_w)
{
	char	*word;

	while (*s == c)
		s++;
	word = ft_substr(s, 0, word_len(s, c));
	if (word == 0)
	{
		free_arr(arr);
		return (0);
	}
	arr[i_w] = word;
	while (*s != c && *s != '\0')
		s++;
	return (s);
}

/*
splits string s based on char c; result is stored in an array of strings
*/
char	**ft_split(char const *s, char c)
{
	char	**return_array;
	size_t	nr_words;
	size_t	i_word;

	if (!s)
		return (NULL);
	nr_words = count_words(s, c);
	return_array = ft_calloc((nr_words + 1), sizeof(char *));
	if (return_array == 0)
		return (0);
	i_word = 0;
	while (i_word < nr_words)
	{
		s = st_wrd(s, c, return_array, i_word);
		if (s == 0)
			return (0);
		i_word++;
	}
	return (return_array);
}
