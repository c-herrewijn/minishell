/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 13:50:16 by kkroon        #+#    #+#                 */
/*   Updated: 2023/05/17 14:31:38 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//need to do 4 on the strncmp for pwd to check for '\0' char

void	check_if_builtin(char *str)
{
	if (ft_strncmp("echo", str, 5) == 0)
		b_echo();
	if (ft_strncmp("cd", str, 3) == 0)
		b_cd();
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
}

void	b_echo(void)
{
	printf("called echo\n");
}

void	b_cd(void)
{
	printf("called cd\n");
}

void	b_pwd(void)
{
	printf("called pwd\n");
	char	s[PATH_MAX];

	getcwd(s, sizeof(s));
	printf("%s\n", s);
}

void	b_export(void)
{
	printf("called export\n");
}

void	b_unset(void)
{
	printf("called unset\n");
}

void	b_env(void)
{
	printf("called env\n");
}

void	b_exit(void)
{
	printf("called exit\n");
	exit(1);
}
