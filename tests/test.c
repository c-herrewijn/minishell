#include "../libft/libft.h"
#include "../sources/minishell.h"
#include <assert.h>

void test_count_tokens(void)
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

int main(void)
{
	test_count_tokens();
}