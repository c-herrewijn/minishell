#include "../libft/libft.h"
#include "../sources/minishell.h"
#include <assert.h>

// static void	str_new_value(char **str_loc, char *new_str)
// {
// 	free(*str_loc);
// 	*str_loc = new_str;
// }

void	test_count_tokens(void)
{
	assert(count_tokens("cat infile") == 2);
	assert(count_tokens("< infile cat") == 3);
	assert(count_tokens("cat < infile") == 3);
	assert(count_tokens("<infile cat") == 3);
	assert(count_tokens("cat<infile") == 3);
	assert(count_tokens("a | b    | c | d | e > outfile < infile") == 13);
	assert(count_tokens("cat infile1 < infile2 infile3") == 5);
	assert(count_tokens("< infile cat | grep aa | wc -l > ouftile") == 11);
	assert(count_tokens("echo aa >> outfile") == 4);

	// check spaces and quotes
	assert(count_tokens("sed 's/hello/replaced by new text/' infile1") == 3);
	assert(count_tokens("echo -n \"hello world\"") == 3);
	assert(count_tokens("echo -n \"hello world\"") == 3);
	assert(count_tokens("   ") == 0);
	assert(count_tokens("echo 'aa > bb'") == 2);

	puts("testing count_tokens OK");
}

void	test_create_tokens(void)
{
	t_data	data;

	data.token_arr = malloc(100 * sizeof(t_token));

	// cases with single spaces
	data.str = "AA BB";
	data.nr_tokens = count_tokens(data.str);
	create_tokens(&data);
	assert(ft_strncmp(tokens_to_string(&data), data.str, ft_strlen(data.str)) == 0);

	data.str = "infile < cat | grep 'hallo hallo' | wc -l > outfile";
	data.nr_tokens = count_tokens(data.str);
	create_tokens(&data);
	assert(ft_strncmp(tokens_to_string(&data), data.str, ft_strlen(data.str)) == 0);

	data.str = "echo \"\"aa\"b\"aa\"\"";
	data.nr_tokens = count_tokens(data.str);
	create_tokens(&data);
	assert(ft_strncmp(tokens_to_string(&data), data.str, ft_strlen(data.str)) == 0);

	// cases with fewer spaces / tabs / more spaces
	data.str = "   ||  aa	cat			>>< aaa    ";
	data.nr_tokens = count_tokens(data.str);
	create_tokens(&data);
	assert(ft_strncmp(tokens_to_string(&data), "| | aa cat >> < aaa", ft_strlen(data.str)) == 0);

	puts("testing create_tokens OK");
	free(data.token_arr);
}

void	test_syntax_validation(void)
{
	t_data	data;

	// valid cases
	data.str = "AA BB";
	lexer(&data);
	assert(syntax_validation(&data) == true);

	data.str = "AA | BB";
	lexer(&data);
	assert(syntax_validation(&data) == true);

	data.str = "";
	lexer(&data);
	assert(syntax_validation(&data) == true);

	// invalid cases
	data.str = "| BB";
	lexer(&data);
	assert(syntax_validation(&data) == false);

	data.str = "BB |";
	lexer(&data);
	assert(syntax_validation(&data) == false);

	data.str = "AA ||| BB";
	lexer(&data);
	assert(syntax_validation(&data) == false);

	data.str = "AA | BB >";
	lexer(&data);
	assert(syntax_validation(&data) == false);

	data.str = "AA | BB >>";
	lexer(&data);
	assert(syntax_validation(&data) == false);

	data.str = ">";
	lexer(&data);
	assert(syntax_validation(&data) == false);

	puts("testing syntax_validation OK");
}

// USER=cherrewi
void	test_expander(void)
{
	t_data		data;
	extern char	**environ;
	t_node		*env_llist;
	char		*exp_str;

	data.envp = environ;
	list_create_env(&env_llist, data);
	data.head = env_llist;

	// printf("%s\n", str1);
	// printf("%s\n", exp_str);
	// printf("len: %zu\n", expanded_str_len(str1, env_llist, &data));

	// no substitution / invalid substitution cases
	char *str1 = "hello";
	exp_str = create_expanded_str(str1, env_llist, &data);
	assert(expanded_str_len(str1, env_llist, &data) == 5);
	assert(ft_strncmp(str1, exp_str, ft_strlen(str1)) == 0);
	free(exp_str);

	char *str2 = "$\"U\"SER";
	exp_str = create_expanded_str(str2, env_llist, &data);
	assert(expanded_str_len(str2, env_llist, &data) == 4);
	assert(ft_strncmp("USER", exp_str, 4) == 0);

	char *str3 = "$\"USER\"";
	exp_str = create_expanded_str(str3, env_llist, &data);
	assert(expanded_str_len(str3, env_llist, &data) == 4);
	assert(ft_strncmp("USER", exp_str, 4) == 0);

	char *str4 = "USERtest$";
	exp_str = create_expanded_str(str4, env_llist, &data);
	assert(expanded_str_len(str4, env_llist, &data) == 9);
	assert(ft_strncmp("USERtest$", exp_str, 9) == 0);

	char *str4b = "$";
	exp_str = create_expanded_str(str4b, env_llist, &data);
	assert(expanded_str_len(str4b, env_llist, &data) == 1);
	assert(ft_strncmp(str4b, exp_str, ft_strlen(str4b)) == 0);

	char *str5 = "USER\"$USERtest\"";
	exp_str = create_expanded_str(str5, env_llist, &data);
	assert(expanded_str_len(str5, env_llist, &data) == 4);
	assert(ft_strncmp("USER", exp_str, 4) == 0);

	char *str6 = "'$USER''$test'";
	exp_str = create_expanded_str(str6, env_llist, &data);
	assert(expanded_str_len(str6, env_llist, &data) == 10);
	assert(ft_strncmp("$USER$test", exp_str, ft_strlen(str6)) == 0);

	char *str7 = "USER \"test\"";
	exp_str = create_expanded_str(str7, env_llist, &data);
	assert(expanded_str_len(str7, env_llist, &data) == 9);
	assert(ft_strncmp("USER test", exp_str, 9) == 0);


	// quote removal cases
	char *str1a = "\"h'ello\"";
	exp_str = create_expanded_str(str1a, env_llist, &data);
	assert(ft_strlen(exp_str) == 6);
	assert(ft_strncmp("h'ello", exp_str, ft_strlen(exp_str)) == 0);
	free(exp_str);

	char *str1b = "h'ell'o";
	exp_str = create_expanded_str(str1b, env_llist, &data);
	assert(ft_strlen(exp_str) == 5);
	assert(ft_strncmp("hello", exp_str, ft_strlen(exp_str)) == 0);
	free(exp_str);

	char *str1c = "'hell'o";
	exp_str = create_expanded_str(str1c, env_llist, &data);
	assert(ft_strlen(exp_str) == 5);
	assert(ft_strncmp("hello", exp_str, ft_strlen(exp_str)) == 0);
	free(exp_str);

	char *str1d = "'hello'";
	exp_str = create_expanded_str(str1d, env_llist, &data);
	assert(ft_strlen(exp_str) == 5);
	assert(ft_strncmp("hello", exp_str, ft_strlen(exp_str)) == 0);
	free(exp_str);

	char *str1e = "h'ello'";
	exp_str = create_expanded_str(str1e, env_llist, &data);
	assert(ft_strlen(exp_str) == 5);
	assert(ft_strncmp("hello", exp_str, ft_strlen(exp_str)) == 0);
	free(exp_str);

	char *str1f = "\"h'ell'o\"";
	exp_str = create_expanded_str(str1f, env_llist, &data);
	assert(ft_strlen(exp_str) == 7);
	assert(ft_strncmp("h'ell'o", exp_str, ft_strlen(exp_str)) == 0);
	free(exp_str);

	char *str1g = "\"'hell'o\"";
	exp_str = create_expanded_str(str1g, env_llist, &data);
	assert(ft_strlen(exp_str) == 7);
	assert(ft_strncmp("'hell'o", exp_str, ft_strlen(exp_str)) == 0);
	free(exp_str);

	char *str1h = "\"'hello'\"";
	exp_str = create_expanded_str(str1h, env_llist, &data);
	assert(ft_strlen(exp_str) == 7);
	assert(ft_strncmp("'hello'", exp_str, ft_strlen(exp_str)) == 0);
	free(exp_str);

	char *str1i = "\"h'ello'\"";
	exp_str = create_expanded_str(str1i, env_llist, &data);
	assert(ft_strlen(exp_str) == 7);
	assert(ft_strncmp("h'ello'", exp_str, ft_strlen(exp_str)) == 0);
	free(exp_str);

	// variable expansion cases
	assert(ft_strncmp("cherrewi", get_value_from_env(env_llist, "USER", 4), 8) == 0);

	char *str10 = "$USER";
	exp_str = create_expanded_str(str10, env_llist, &data);
	assert(expanded_str_len(str10, env_llist, &data) == 8);
	assert(ft_strncmp("cherrewi", exp_str, 8) == 0);
	free(exp_str);

	char *str10a = "$USE";
	exp_str = create_expanded_str(str10a, env_llist, &data);
	assert(expanded_str_len(str10a, env_llist, &data) == 0);
	assert(exp_str[0] == '\0');
	free(exp_str);

	char *str10b = "a$USE";
	exp_str = create_expanded_str(str10b, env_llist, &data);
	assert(expanded_str_len(str10b, env_llist, &data) == 1);
	assert(ft_strncmp("a", exp_str, 1) == 0);
	free(exp_str);

	char *str11 = "USER\"test$USER\"";
	exp_str = create_expanded_str(str11, env_llist, &data);
	assert(expanded_str_len(str11, env_llist, &data) == 16);
	assert(ft_strncmp("USERtestcherrewi", exp_str, 16) == 0);
	free(exp_str);

	char *str12 = "USER\"$USER test\"";
	assert(expanded_str_len(str12, env_llist, &data) == 17);
	exp_str = create_expanded_str(str12, env_llist, &data);
	assert(ft_strncmp("USERcherrewi test", exp_str, 17) == 0);
	free(exp_str);

	char *str12a = "USER\"$USER\ttest\"";
	assert(expanded_str_len(str12a, env_llist, &data) == 17);
	exp_str = create_expanded_str(str12a, env_llist, &data);
	assert(ft_strncmp("USERcherrewi\ttest", exp_str, 17) == 0);
	free(exp_str);

	char *str13 = "$USER'$test'";
	assert(expanded_str_len(str13, env_llist, &data) == 13);
	exp_str = create_expanded_str(str13, env_llist, &data);
	assert(ft_strncmp("cherrewi$test", exp_str, 13) == 0);
	free(exp_str);

	char *str14 = "USER$USER\"test$USER\"";	// 24
	exp_str = create_expanded_str(str14, env_llist, &data);
	assert(expanded_str_len(str14, env_llist, &data) == 24);
	assert(ft_strncmp("USERcherrewitestcherrewi", exp_str, 24) == 0);
	free(exp_str);

	char *str15 = "$USERUSER\"test$USER\"";	// 12
	exp_str = create_expanded_str(str15, env_llist, &data);
	assert(expanded_str_len(str15, env_llist, &data) == 12);
	assert(ft_strncmp("testcherrewi", exp_str, 12) == 0);
	free(exp_str);

	char *str16 = "'$USER'USER$USER\"test$USER\""; //29
	exp_str = create_expanded_str(str16, env_llist, &data);
	assert(expanded_str_len(str16, env_llist, &data) == 29);
	assert(ft_strncmp("$USERUSERcherrewitestcherrewi", exp_str, 29) == 0);
	free(exp_str);

	char *str17 = "bb$USER"; //10
	exp_str = create_expanded_str(str17, env_llist, &data);
	assert(expanded_str_len(str17, env_llist, &data) == 10);
	assert(ft_strncmp("bbcherrewi", exp_str, 10) == 0);
	free(exp_str);

	char *str18 = "$USER$USER"; //16
	exp_str = create_expanded_str(str18, env_llist, &data);
	assert(expanded_str_len(str18, env_llist, &data) == 16);
	assert(ft_strncmp("cherrewicherrewi", exp_str, 16) == 0);
	free(exp_str);

	char *str19 = "$USER$"; //9
	exp_str = create_expanded_str(str19, env_llist, &data);
	assert(expanded_str_len(str19, env_llist, &data) == 9);
	assert(ft_strncmp("cherrewi$", exp_str, 9) == 0);
	free(exp_str);

	char *str20 = "$$USER"; //9  NOTE this is different from bash, because bash has special purpose for '$$'
	exp_str = create_expanded_str(str20, env_llist, &data);
	assert(expanded_str_len(str20, env_llist, &data) == 9);
	assert(ft_strncmp("$cherrewi", exp_str, 9) == 0);
	free(exp_str);

	char *str20b = "\"$USER$\"";
	exp_str = create_expanded_str(str20b, env_llist, &data);
	assert(expanded_str_len(str20b, env_llist, &data) == 9);
	assert(ft_strncmp("cherrewi$", exp_str, 9) == 0);
	free(exp_str);

	char *str20c = "\"$USER$''\"";
	exp_str = create_expanded_str(str20c, env_llist, &data);
	assert(expanded_str_len(str20c, env_llist, &data) == 11);
	assert(ft_strncmp("cherrewi$''", exp_str, 11) == 0);
	free(exp_str);

	char *str20d = "\"$USER'''\"";
	exp_str = create_expanded_str(str20d, env_llist, &data);
	assert(expanded_str_len(str20d, env_llist, &data) == 11);
	assert(ft_strncmp("cherrewi'''", exp_str, 11) == 0);
	free(exp_str);

	char *str20e = "\"$USE'''\"";
	exp_str = create_expanded_str(str20e, env_llist, &data);
	assert(expanded_str_len(str20e, env_llist, &data) == 3);
	assert(ft_strncmp("'''", exp_str, 3) == 0);
	free(exp_str);

	char *str20f = "\"$'USER'\"";
	exp_str = create_expanded_str(str20f, env_llist, &data);
	assert(expanded_str_len(str20f, env_llist, &data) == 7);
	assert(ft_strncmp("$'USER'", exp_str, 7) == 0);
	free(exp_str);

	char *str20g = "$''a";
	exp_str = create_expanded_str(str20g, env_llist, &data);
	assert(expanded_str_len(str20g, env_llist, &data) == 1);
	assert(ft_strncmp("a", exp_str, 1) == 0);
	free(exp_str);

	// heredoc cases, ending with newline

	char *str21 = "aa$USER\n";
	exp_str = create_expanded_str(str21, env_llist, &data);
	assert(expanded_str_len(str21, env_llist, &data) == 11);
	assert(ft_strncmp("aacherrewi\n", exp_str, 11) == 0);
	free(exp_str);

	char *str22 = "aa$USER$\n";
	exp_str = create_expanded_str(str22, env_llist, &data);
	assert(expanded_str_len(str22, env_llist, &data) == 12);
	assert(ft_strncmp("aacherrewi$\n", exp_str, 12) == 0);
	free(exp_str);

	char *str23 = "aa$USER \n";
	exp_str = create_expanded_str(str23, env_llist, &data);
	assert(expanded_str_len(str23, env_llist, &data) == 12);
	assert(ft_strncmp("aacherrewi \n", exp_str, 12) == 0);
	free(exp_str);

	char *str24 = "aa$USER+\n";
	exp_str = create_expanded_str(str24, env_llist, &data);
	assert(expanded_str_len(str24, env_llist, &data) == 12);
	assert(ft_strncmp("aacherrewi+\n", exp_str, 12) == 0);
	free(exp_str);

	// $? case
	data.previous_exit_status = 42;

	char *str25 = "$?";
	exp_str = create_expanded_str(str25, env_llist, &data);
	assert(expanded_str_len(str25, env_llist, &data) == 2);
	assert(ft_strncmp("42", exp_str, 2) == 0);
	free(exp_str);

	char *str26 = "$USER?";
	exp_str = create_expanded_str(str26, env_llist, &data);
	assert(expanded_str_len(str26, env_llist, &data) == 9);
	assert(ft_strncmp("cherrewi?", exp_str, 9) == 0);
	free(exp_str);

	char *str27 = "$?$USER";
	exp_str = create_expanded_str(str27, env_llist, &data);
	assert(expanded_str_len(str27, env_llist, &data) == 10);
	assert(ft_strncmp("42cherrewi", exp_str, 10) == 0);
	free(exp_str);

	char *str28 = "aa$?bb";
	exp_str = create_expanded_str(str28, env_llist, &data);
	assert(expanded_str_len(str28, env_llist, &data) == 6);
	assert(ft_strncmp("aa42bb", exp_str, 6) == 0);
	free(exp_str);

	char *str29 = "aa$?\n";
	exp_str = create_expanded_str(str29, env_llist, &data);
	assert(expanded_str_len(str29, env_llist, &data) == 5);
	assert(ft_strncmp("aa42\n", exp_str, 5) == 0);
	free(exp_str);

	data.previous_exit_status = 0;
	char *str29b = "aa$?\n";
	exp_str = create_expanded_str(str29b, env_llist, &data);
	assert(expanded_str_len(str29b, env_llist, &data) == 4);
	assert(ft_strncmp("aa0\n", exp_str, 4) == 0);
	free(exp_str);

	data.previous_exit_status = 127;
	char *str29c = "aa$?\n";
	exp_str = create_expanded_str(str29c, env_llist, &data);
	assert(expanded_str_len(str29c, env_llist, &data) == 6);
	assert(ft_strncmp("aa127\n", exp_str, 6) == 0);
	free(exp_str);

	puts("testing expander OK");
}

void test_cd_pwd(void)
{
	//mkdir testyep
	//cd testyep
	//rm -rf ../testyep
}

//this can mosly actually be tested in main function
//because in the main input like export TESTYEP+="$REAL$FAKE$rEaL \n\n\n\n\n" is parsed, lexed, expanded
void test_env_export_unset(void)
{

}

void test_echo(void) //run the executioner from bash when using system
{
	t_data		data;
	extern char	**environ;
	t_node		*env_llist;

	data.envp = environ;
	list_create_env(&env_llist, data);
	int argc = 4;
	char *argv[] = {"echo", "-nnnnnnnnn", "-nnnbnn", "testyep"};
	assert(b_echo(argc, argv) == 0);
	// system("echo -nnnnnnnnn -nnnbnn testyep");
	printf("\n");
	int pid = fork();
	if(pid == 0)
	{
		char *cmd = "/bin/echo";
		char *args[] = {"echo -nnnnnnnnn", "-nnnbnn", "testyep", NULL};
		execve(cmd, args, NULL);
		_exit(1);
	}
	/*
	---updates infile
	$>echo -n yep > infile

	---does not update infile
	/Users/kkroon/codam/minishell % ./minishell
	minishell$ echo -n ok > infile
	okminishell$
	*/
}

void test_exit(void)
{
	//exits cleanly
	//correct exit status?
}

void test_random(void)
{
	//maybe like shlvl and stuff
	//test awk
	//test executer
}

int g_signumber;

int main(void)
{
	test_count_tokens();
	test_create_tokens();
	test_syntax_validation();
	test_expander();
	// test_echo();
	exit(0);
}
