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


int main(void)
{
	test_count_tokens();
	test_create_tokens();
}
