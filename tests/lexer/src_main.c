#include "../inc/tests.h"

int main() 
{
	test_quotes("files/quotes.txt", 0, 1);
	test_lexer("files/lexer.txt", 2, 3);
	return (0);
}
