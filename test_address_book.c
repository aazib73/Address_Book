#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "unity.h"
#include "address_book.h"
#include "address_book_fops.h"
#include "address_book_menu.h"

void setUp(void) {

}

void tearDown(void) {

}

void test_get_option_char_single() {
    FILE *p = fopen("stdin.txt", "w"); //preparing fake inputs
    fprintf(p, "a\n");
    fclose(p);
    freopen("stdin.txt", "r", stdin);
    fclose(stdin);

    char result = get_option(CHAR, "");
    TEST_ASSERT_EQUAL('a', result);
}

void test_get_option_char_multiple() {
    FILE * p = fopen("stdin.txt", "w"); //preparing fake inputs
    fprintf(p , "abc\n");
    fclose(p);
    freopen("stdin.txt", "r", stdin);
    flose(stdin);

    int result = get_option(CHAR, "");
    TEST_ASSERT_EQUAL('a', result);
}

void test_get_option_int() {
    FILE * p = fopen("stdin.txt", "w");
    fprintf(p, "53");
    fclose(p);
    freopen("stdin.txt", "r", stdin);
    fclose(stdin);

    int result = get_option(NUM, "");
    TEST_ASSERT_EQUAL(53, result);
}

void test_get_option_none() {
    FILE * p = fopen("stdin.txt", "w");
    fprinf(p, "123");   
    fclose(p);
    freopen("stdin.txt", "r", stdin);
    fclose(stdin);

    int result = get_option(NONE, "");
    TEST_ASSERT_EQUAL(0, result);
}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_get_option_char_single);
    RUN_TEST(test_get_option_char_multiple);
    RUN_TEST(test_get_option_int);
    RUN_TEST(test_get_option_none);
    return UNITY_END();
}