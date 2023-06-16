#include "../libft/libft.h"
#include "../sources/minishell.h"
#include <assert.h>

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
	char	*token_str;

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
void	test_expanded_str_len(void)
{
	t_data		data;
	extern char	**environ;
	t_node		*env_llist;
	char		*exp_str;

	data.envp = environ;
	list_create_env(&env_llist, data);

	// no substitution / invalid substitution cases
	char *str1 = "hello";
	printf("str1: %s\n", str1);
	printf("len: %zu\n", expanded_str_len(str1, env_llist));

	exp_str = create_expanded_str(str1, env_llist);
	printf("exp_str: %s\n", exp_str);

	assert(expanded_str_len(str1, env_llist) == 5);
	
	char *str2 = "$\"U\"SER";
	assert(expanded_str_len(str2, env_llist) == 4);

	char *str3 = "$\"USER\"";
	assert(expanded_str_len(str3, env_llist) == 4);

	char *str4 = "USERtest$";
	assert(expanded_str_len(str4, env_llist) == 9);

	char *str4b = "$";
	assert(expanded_str_len(str4b, env_llist) == 1);
	
	char *str5 = "USER\"$USERtest\"";
	assert(expanded_str_len(str5, env_llist) == 4);

	char *str6 = "'$USER''$test'";
	assert(expanded_str_len(str6, env_llist) == 10);

	char *str7 = "USER \"test\"";
	assert(expanded_str_len(str7, env_llist) == 9);

	// regular cases
	char *str10 = "$USER";
	assert(expanded_str_len(str10, env_llist) == 8);
	
	char *str10a = "$USE";
	assert(expanded_str_len(str10a, env_llist) == 0);
	
	char *str10b = "a$USE";
	assert(expanded_str_len(str10b, env_llist) == 1);

	char *str11 = "USER\"test$USER\"";
	assert(expanded_str_len(str11, env_llist) == 16);

	char *str12 = "USER\"$USER test\"";
	assert(expanded_str_len(str12, env_llist) == 17);
	
	char *str13 = "$USER'$test'";
	assert(expanded_str_len(str13, env_llist) == 13);

	char *str14 = "USER$USER\"test$USER\"";	// 24
	assert(expanded_str_len(str14, env_llist) == 24);
	
	char *str15 = "$USERUSER\"test$USER\"";	// 12
	assert(expanded_str_len(str15, env_llist) == 12);
	
	char *str16 = "'$USER'USER$USER\"test$USER\""; //29
	assert(expanded_str_len(str16, env_llist) == 29);
	
	char *str17 = "bb$USER"; //10
	assert(expanded_str_len(str17, env_llist) == 10);
	
	char *str18 = "$USER$USER"; //16
	assert(expanded_str_len(str18, env_llist) == 16);
	
	char *str19 = "$USER$"; //9
	assert(expanded_str_len(str19, env_llist) == 9);

	char *str20 = "$$USER"; //9  NOTE this is different from bash, because bash has special purpose for '$$'
	assert(expanded_str_len(str20, env_llist) == 9);
	puts("testing expanded_str_len OK");
}




int main(void)
{
	test_count_tokens();
	test_create_tokens();
	test_syntax_validation();
	test_expanded_str_len();
	exit(0);
}
