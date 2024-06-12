#include "../../include/minishell.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void compare(const char *input, const char *expected);

void create_test_file(const char *test_file, int col1_index, int col2_index);
void test_quotes(const char *test_file, int col1_index, int col2_index);
void test_lexer(const char *test_file, int col1_index, int col2_index);