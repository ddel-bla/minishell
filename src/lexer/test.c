#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../include/minishell.h"

void validate_test (int condition,  char *test_name)
{
    if (condition)
        printf("\033[0;32m[PASS] %s\033[0m\n", test_name);
    else
        printf("\033[0;31m[FAIL] %s\033[0m\n", test_name);
}

void validate_test2(int condition,  char *test_name)
{
    if (!condition)
        printf("\033[0;32m[PASS] %s\033[0m\n", test_name);
    else
        printf("\033[0;31m[FAIL] %s\033[0m\n", test_name);
}


void run_tests()
{
    t_token *token_list = NULL;

    // Test 1: Simple command
    char input1[] = "echo hello";
    lexer(input1, &token_list);
    printf("\n\033[0;32mTEST Nº 1\033[0m\n");
    printf("Expected: %d\n", 2);
    printf("Actual: %d\n", lst_size(token_list));
    validate_test(lst_size(token_list) == 2, "SIZE");
    printf("Expected: %s\n", "echo");
    printf("Actual: %s\n", get_token_by_index(token_list, 0)->value);
    validate_test2(get_token_by_index(token_list, 0)->value == "echo", "TOKENS");
    printf("Expected: %s\n", "hello");
    printf("Actual: %s\n", get_token_by_index(token_list, 1)->value);
    validate_test2(get_token_by_index(token_list, 1)->value == "hello", "TOKENS");   
    free_lst(token_list);
    token_list = NULL;
    printf("------------------------------------------------------------");
    
    // Test 1: Commmand with simple quotes
    char input2[] = "echo 'hello world'";
    lexer(input2, &token_list);
    printf("\n\033[0;32mTEST Nº 2\033[0m\n");
    printf("Expected: %d\n", 2);
    printf("Actual: %d\n", lst_size(token_list));
    validate_test(lst_size(token_list) == 2, "SIZE");
    printf("Expected: %s\n", "echo");
    printf("Actual: %s\n", get_token_by_index(token_list, 0)->value);
    validate_test2(get_token_by_index(token_list, 0)->value == "echo", "TOKENS");
    printf("Expected: %s\n", "hello world");
    printf("Actual: %s\n", get_token_by_index(token_list, 1)->value);
    validate_test2(get_token_by_index(token_list, 1)->value == "hello world", "TOKENS");
    free_lst(token_list);
    token_list = NULL;
    printf("------------------------------------------------------------");


    // Test 3: Command with pipes
    char input3[] = "echo hello | grep hello";
    lexer(input3, &token_list);
    printf("\n\033[0;32mTEST Nº 3\033[0m\n");
    printf("Expected: %d\n", 5);
    printf("Actual: %d\n", lst_size(token_list));
    validate_test(lst_size(token_list) == 5, "SIZE");
    printf("Expected: %s\n", "echo");
    printf("Actual: %s\n", get_token_by_index(token_list, 0)->value);
    validate_test2(get_token_by_index(token_list, 0)->value == "echo", "TOKENS");
    printf("Expected: %s\n", "hello");
    printf("Actual: %s\n", get_token_by_index(token_list, 1)->value);
    validate_test2(get_token_by_index(token_list, 1)->value == "hello", "TOKENS");
    printf("Expected: %s\n", "|");
    printf("Actual: %s\n", get_token_by_index(token_list, 2)->value);
    validate_test2(get_token_by_index(token_list, 2)->value == "|", "TOKENS");
    printf("Expected: %s\n", "grep");
    printf("Actual: %s\n", get_token_by_index(token_list, 3)->value);
    validate_test2(get_token_by_index(token_list, 3)->value == "grep", "TOKENS");
    printf("Expected: %s\n", "hello");
    printf("Actual: %s\n", get_token_by_index(token_list, 4)->value);
    validate_test2(get_token_by_index(token_list, 4)->value == "hello", "TOKENS");
    free_lst(token_list);
    token_list = NULL;
    printf("------------------------------------------------------------");

    // Test 4: Commmand with double quotes
    char input4[] = "echo \"hello world\"";
    lexer(input4, &token_list);
    printf("\n\033[0;32mTEST Nº 2\033[0m\n");
    printf("Expected: %d\n", 2);
    printf("Actual: %d\n", lst_size(token_list));
    validate_test(lst_size(token_list) == 2, "SIZE");
    printf("Expected: %s\n", "echo");
    printf("Actual: %s\n", get_token_by_index(token_list, 0)->value);
    validate_test2(get_token_by_index(token_list, 0)->value == "echo", "TOKENS");
    printf("Expected: %s\n", "hello world");
    printf("Actual: %s\n", get_token_by_index(token_list, 1)->value);
    validate_test2(get_token_by_index(token_list, 1)->value == "hello world", "TOKENS");
    free_lst(token_list);
    token_list = NULL;
    printf("------------------------------------------------------------");

    // Test 5: Empty input
    char input5[] = "";
    lexer(input5, &token_list);
    printf("\n\033[0;32mTEST Nº 5\033[0m\n");
    printf("Expected: %d\n", 0);
    printf("Actual: %d\n", lst_size(token_list));
    validate_test(lst_size(token_list) == 0, "SIZE");
    free_lst(token_list);
    token_list = NULL;
    printf("------------------------------------------------------------");

    // Test 6: Only spaces
    char input6[] = "     ";
    lexer(input6, &token_list);
    printf("\n\033[0;32mTEST Nº 6\033[0m\n");
    printf("Expected: %d\n", 0);
    printf("Actual: %d\n", lst_size(token_list));
    validate_test(lst_size(token_list) == 0, "SIZE");
    free_lst(token_list);
    token_list = NULL;
    printf("------------------------------------------------------------");

    // Test 7: Complex command
    char input7[] = "cat file.txt | grep 'pattern' | sort > output.txt";
    lexer(input7, &token_list);
    printf("\n\033[0;32mTEST Nº 7\033[0m\n");
    printf("Expected: %d\n", 9);
    printf("Actual: %d\n", lst_size(token_list));
    validate_test(lst_size(token_list) == 9, "SIZE");
    printf("Expected: %s\n", "cat");
    printf("Actual: %s\n", get_token_by_index(token_list, 0)->value);
    validate_test2(get_token_by_index(token_list, 0)->value == "cat", "TOKENS");
    printf("Expected: %s\n", "file.txt");
    printf("Actual: %s\n", get_token_by_index(token_list, 1)->value);
    validate_test2(get_token_by_index(token_list, 1)->value == "file.txt", "TOKENS");
    printf("Expected: %s\n", "|");
    printf("Actual: %s\n", get_token_by_index(token_list, 2)->value);
    validate_test2(get_token_by_index(token_list, 2)->value == "|", "TOKENS");
    printf("Expected: %s\n", "file.txt");
    printf("Actual: %s\n", get_token_by_index(token_list, 3)->value);
    validate_test2(get_token_by_index(token_list, 3)->value == "grep", "TOKENS");
    printf("Expected: %s\n", "grep");
    printf("Actual: %s\n", get_token_by_index(token_list, 4)->value);
    validate_test2(get_token_by_index(token_list, 4)->value == "pattern", "TOKENS");
    printf("Expected: %s\n", "|");
    printf("Actual: %s\n", get_token_by_index(token_list, 5)->value);
    validate_test2(get_token_by_index(token_list, 5)->value == "|", "TOKENS");
    printf("Expected: %s\n", "sort");
    printf("Actual: %s\n", get_token_by_index(token_list, 6)->value);
    validate_test2(get_token_by_index(token_list, 6)->value == "sort", "TOKENS");
    printf("Expected: %s\n", ">");
    printf("Actual: %s\n", get_token_by_index(token_list, 7)->value);
    validate_test2(get_token_by_index(token_list, 7)->value == ">", "TOKENS");
    printf("Expected: %s\n", "output.txt");
    printf("Actual: %s\n", get_token_by_index(token_list, 8)->value);
    validate_test2(get_token_by_index(token_list, 8)->value == "output.txt", "TOKENS");
    free_lst(token_list);
    token_list = NULL;
    printf("------------------------------------------------------------\n");
}

int main(void)
{
    run_tests();
}
