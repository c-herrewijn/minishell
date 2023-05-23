/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 12:44:41 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/05/23 15:10:22 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nr_tokens)
	{
		free(data->token_arr[i].word);
		i++;
	}
	free(data->token_arr);
	data->nr_tokens = 0;
	data->token_arr = NULL;
}

// takes input line excluding linebreak
int	lexer(t_data *data)
{
	if (data->str == NULL || *data->str == '\0')
		return (0);
	data->nr_tokens = count_tokens(data->str);
	if (data->nr_tokens == 0)
		return (0);
	data->token_arr = ft_calloc((data->nr_tokens + 1), sizeof(t_token));
	if (data->token_arr == NULL)
		return (-1);
	if (create_tokens(data) < 0)
		return (-1);
	return (0);
}
