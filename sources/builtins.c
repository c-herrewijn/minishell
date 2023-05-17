/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 13:50:16 by kkroon        #+#    #+#                 */
/*   Updated: 2023/05/17 15:56:06 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//need to do 4 on the strncmp for pwd to check for '\0' char

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

void	check_if_builtin(char *str, char **envp)
{
	if (ft_strncmp("echo", str, 5) == 0)
		b_echo();
	if (ft_strncmp("cd", str, 2) == 0)
		b_cd(str, envp);
	if (ft_strncmp("pwd", str, 4) == 0)
		b_pwd();
	if (ft_strncmp("export", str, 7) == 0)
		b_export();
	if (ft_strncmp("unset", str, 6) == 0)
		b_unset();
	if (ft_strncmp("env", str, 4) == 0)
		b_env();
	if (ft_strncmp("exit", str, 5) == 0)
		b_exit();
	(void) envp;
}

void	b_echo(void)
{
}

void	b_cd(char *str, char **envp)
{
	char **home_path;
	char **cd_path;
	home_path = ft_split(envp[2], '=');
	cd_path = ft_split(str, ' ');

	if (b_arr_len(cd_path) <= 1)
	{
		chdir(home_path[1]);
		b_free_arr(home_path);
		b_free_arr(cd_path);
		b_pwd();
	}
	else
	{
		chdir(cd_path[1]);
		b_free_arr(home_path);
		b_free_arr(cd_path);
		b_pwd();
	}
}

void	b_pwd(void)
{
	char	s[PATH_MAX];

	getcwd(s, sizeof(s));
	printf("%s\n", s);
}

void	b_export(void)
{
}

void	b_unset(void)
{
}

void	b_env(void)
{
}

void	b_exit(void)
{
	exit(1);
}
