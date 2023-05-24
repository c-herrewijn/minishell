#include "echoheader.h"

int		len_2d_arr(char **arr)
{
	int i;

	i = 0;
	while(arr[i] != NULL)
	{
		i++;
	}
	return i;
}

void	free_2d_arr(char **arr)
{
	int i;

	i = 0;
	while(arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

size_t	ft_strlen(const char *s)
{
	size_t	c;

	if (s == NULL)
		return (0);
	c = 0;
	while (*s)
	{
		s++;
		c++;
	}
	return (c);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	size_t	i;

	str = malloc(count * size);
	if (str == NULL)
		return (str);
	i = 0;
	while (i < (count * size))
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}

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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*new_str;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		new_str = malloc(1 * sizeof(char));
	else if (ft_strlen(s) - start > len)
		new_str = malloc(len + 1 * sizeof(char));
	else
		new_str = malloc((ft_strlen(s) - start + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s) - start && i < len && start < ft_strlen(s))
	{
		new_str[i] = s[i + start];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

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
