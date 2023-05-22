/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 12:44:41 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/05/22 20:23:43 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *token_arr, t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nr_tokens)
	{
		free(token_arr[i].word);
		i++;
	}
	free(token_arr);
	data->nr_tokens = 0;
}

// takes input line excluding linebreak
t_token	*lexer(t_data *data)
{
	t_token			*token_arr;

	if (data->str == NULL || *data->str == '\0')
		return (NULL);
	data->nr_tokens = count_tokens(data->str);
	if (data->nr_tokens == 0)
		return (NULL);
	token_arr = ft_calloc((data->nr_tokens + 1), sizeof(t_token));
	if (token_arr == NULL)
		return (NULL);
	create_tokens(data->str, token_arr);
	return (token_arr);
}
