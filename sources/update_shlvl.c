/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_shlvl.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 20:42:35 by kkroon        #+#    #+#                 */
/*   Updated: 2023/06/19 21:21:17 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
all good : ret start of num
SHLVL needs to be set to 1 : ret 1
*/
static int shlvl_check(char *str)
{
	int i;
	int loc;

	loc = 0;
	i = 0;
	printf("DEBUG shlvl_check() : str : %s\n", str);	
	if (str[i] == '\0')
		return (-2);
	while (str[i] != '\0' && ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	loc = i;
	printf("DEBUG shlvl_check() : i : %d, str[i] : %c\n", i, str[i]);
	if (!ft_isdigit(str[i]))
		return (-2);
	printf("DEBUG shlvl_check() : i : %d, str[i] : %c\n", i, str[i]);
	while (str[i] != '\0' && ft_isdigit(str[i]))
		i++;
	while(str[i] != '\0')
	{
		if (!ft_isspace(str[i]))
			return (-2);
		i++;
	}
	printf("DEBUG shlvl_check() : i : %d, str[i] : %c\n", i, str[i]);
	return (loc);
}

static int set_shlvl(t_node *node, char *val, bool to_free)
{
	char *str;
	
	printf("DEBUG set_shlvl() : val : %s\n", val);	
	str = ft_strjoin("SHLVL=", val);
	if (to_free == true)
		free(val);
	if (str == NULL)
		return (-1);
	free(node->str);
	node->str = str;
	printf("DEBUG set_shlvl() : str : %s, node->str : %s\n", str, node->str);
	return (0);
}

static int increment_shlvl(t_node *node, char *str, int loc)
{
	long long n;
	int i;

	n = 0;
	i = loc;
	while(str[i] != '\0' && ft_isdigit(str[i]))
	{
		n = n * 10;
		n = n + (str[i] - '0');
		i++;
		if ((i - loc) > 12)
			break;
	}
	if (loc == 0)
		loc++;
	if (str[loc-1] == '-')
		n = n * -1;
	if (n > INT_MIN && n < 0)
		return(set_shlvl(node, "0", false));
	if (n == 999)
		return(set_shlvl(node, "", false));
	if (n < INT_MIN || n == 0 || n > 999)
		return(set_shlvl(node, "1", false));
	n = n + 1;
	return(set_shlvl(node, ft_itoa(n), true));
}

/*
increment shlvl, find node and change it, ft_atoi
after some testing and googling, the cap of SHLVL is at 999

* set to SHLVL=0
	- value > INT_MIN && value < 0
* set to SHLVL=1
	- value < INT_MIN || value > 999
	- non whitespice infront of value
	- non whitespice after last connected number
	- SHLVL is unset
	- value doesnt exist
* set to SHLVL=
	- value is 999
*/
int	update_shlvl(t_node **head, t_data data)
{
	t_node	*node;
	int		index;
	char	*str;
	int		ret;

	index = index_in_env("none", "SHLVL", head);
	if (index == -1)
	{
		printf("DEBUG : NO SHLVL FOUND\n");	
		str = ft_strjoin("SHLVL=", "1");
		if (str == NULL)
			return (-1);
		if (list_append(head, str) == -1)
			return (-1);
		return (0);
	}
	node = get_node_from_index(head, index);
	ret = shlvl_check(node->str + ft_strlen("SHLVL="));
	if (ret == -2)
	{
		printf("DEBUG : INVALID SHLVL, setting back to 1\n");	
		return(set_shlvl(node, "1", false));
	}
	if (increment_shlvl(node, node->str + ft_strlen("SHLVL="), ret) == -1)
		return (-1);
	printf("DEBUG : node->str : %s\n", node->str);
	return (0);
}
