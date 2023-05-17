/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 13:50:16 by kkroon        #+#    #+#                 */
/*   Updated: 2023/05/17 20:37:50 by kkroon        ########   odam.nl         */
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
	if (ft_strncmp("echo", str, 4) == 0)
		b_echo(str);
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

void	b_cd(char *str, char **envp)
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
