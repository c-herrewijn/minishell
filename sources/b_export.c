/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   b_export.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 12:26:47 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/20 15:07:49 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//if in, concat inplace
//if not in, append to the env linked list
int	b_export_concat(char **argv, t_node **head)
{
	char	*without_plus;

	without_plus = remove_plus(argv[1]);
	if (without_plus == NULL)
		return (-1);
	if (empty_list_add(head, without_plus) == true)
		return (0);
	if (concat_helper(argv, head, without_plus) == -1)
		return (-1);
	return (0);
}

//unset then export
//cpy is basicly same as argv[1]
//argv[0] export
//argv[1] name=value
int	b_export(int argc, char **argv, t_node **head)
{
	char	*cpy;

	cpy = ft_substr(argv[1], 0, ft_strlen(argv[1]));
	if (cpy == NULL)
		return (-1);
	if (empty_list_add(head, cpy) == true)
		return (0);
	b_unset(argc, argv, head);
	if (empty_list_add(head, cpy) == true)
		return (0);
	if (list_append(head, cpy) == -1)
	{
		free(cpy);
		return (-1);
	}
	return (0);
}

int	execute_export(t_node **head, t_data *data, size_t i)
{
	int		export_format;
	char	**argv;
	int		ret;

	ret = 0;
	argv = data->command_arr[i].argv;
	export_format = b_export_allowed_format(argv);
	if (export_format < 0)
	{
		write(2, "export: `", 9);
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, "': not a valid identifier\n", 26);
		return (1);
	}
	if (argv[1][0] == '_'
			&& (argv[1][1] == '\0' || argv[1][1] == '=' || argv[1][1] == '+'))
		return (ret);
	if (export_format == 1)
		ret = b_export(data->command_arr[i].argc, argv, head);
	else if (export_format == 2)
		ret = b_export_concat(argv, head);
	return (ret);
}
