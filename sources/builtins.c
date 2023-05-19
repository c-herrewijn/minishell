/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 13:50:16 by kkroon        #+#    #+#                 */
/*   Updated: 2023/05/19 19:42:16 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_free_arr(char **s)
{
	int i;

	i = 0;
	while(s[i] != NULL)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

int		b_arr_len(char **s)
{
	int i;

	i = 0;
	while(s[i] != NULL)
	{
		i++;
	}
	return i;
}

void	check_if_builtin(char *str, t_node **head)
{
	if (ft_strncmp("echo ", str, 5) == 0)
		b_echo(str);
	if (ft_strncmp("cd ", str, 3) == 0)
		b_cd(str, head);
	if (ft_strncmp("pwd", str, 4) == 0)
		b_pwd();
	if (ft_strncmp("export ", str, 7) == 0)
		b_export(str, head);
	if (ft_strncmp("unset ", str, 6) == 0)
		b_unset(str, head);
	if (ft_strncmp("env", str, 4) == 0)
		b_env(str, head);
	if (ft_strncmp("exit", str, 5) == 0)
		b_exit();
	if (ft_strncmp("$", str, 1) == 0)
		print_env_var(str, *head);
}

void	b_echo(char *str)
{
	int len;
	int nlflag;
	int i;

	i = 5;
	nlflag = true;
	len = (int)ft_strlen(str);
	if (len <= 5)
		return ;
	if (len >= 7)
	{
		if (str[5] == '-' && str[6] == 'n')
		{
			nlflag = false;
			i = 7;
		}	
	}
	printf("%s", str + i);
	if (nlflag == true)
		printf("\n");
}

//need to update the env when cd is succesfull
void	b_cd(char *str, t_node **head)
{
	char **cd_path;
	cd_path = ft_split(str, ' ');

	if (b_arr_len(cd_path) <= 1)
	{
		chdir(getenv("HOME"));
		b_free_arr(cd_path);
	}
	else if (cd_path[1][0] == '~' && cd_path[1][1] == '\0') // up for interpetation
	{
		chdir(getenv("HOME"));
		b_free_arr(cd_path);
	}
	else
	{
		chdir(cd_path[1]);
		b_free_arr(cd_path);
	}
}

//should still be able to do pwd command even if PWD is unset
void	b_pwd(void)
{
	char	s[PATH_MAX];

	getcwd(s, sizeof(s));
	printf("%s\n", s);
}

//unset then export
//might want to update existing env var in place if it already exists
void	b_export(char *str, t_node **head)
{
	b_unset(str, head);
	list_append(head, str + 7);
}

//not working yet, might be something with how i use strncmp
//or might be something to do with the list_remove_index function
void	b_unset(char *str, t_node **head)
{
	t_node *node;
	int str_len;
	int i;

	node = *head;
	str_len = (int)ft_strlen(str) - 6;
	if (str_len <= 1)
		return ;
	i = 0;
	while(node != NULL)
	{
		if (ft_strncmp(str, node->str, str_len) == 0)
		{
			// if ((node->str)[str_len] == '=')
			// {
			list_remove_index(head, i);
			// }
			return ;
		}
		i++;
		node = node->next;
	}
}

void	b_env(char *str, t_node **head)
{
	list_print(*head);
}

void	b_exit(void)
{
	exit(1);
}
