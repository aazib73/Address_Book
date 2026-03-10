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

void prepare_stdin(FILE * p, char * input) {
    p = fopen("stdin.txt", "w");
    fprintf(p, "%s", input);
    fclose(p);
    freopen("stdin.txt", "r", stdin);
}

void test_get_option_char_single() {
    FILE * p; 
    prepare_stdin(p, "f\n");

    char result = get_option(CHAR, "");
    TEST_ASSERT_EQUAL('f', result);
    fclose(stdin);
}

void test_get_option_char_multiple() {
    FILE * p;
    prepare_stdin(p, "cba\n");

    int result = get_option(CHAR, "");
    TEST_ASSERT_EQUAL('c', result);
    fclose(stdin);
}

void test_get_option_int() {
    FILE * p;
    prepare_stdin(p, "53\n");

    int result = get_option(NUM, "");
    TEST_ASSERT_EQUAL(53, result);
    fclose(stdin);
}

void test_get_option_none() {
    FILE * p;
    prepare_stdin(p, "123\n");

    int result = get_option(NONE, "");
    TEST_ASSERT_EQUAL(0, result);
    fclose(stdin);
}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_get_option_char_single);
    RUN_TEST(test_get_option_char_multiple);
    RUN_TEST(test_get_option_int);
    RUN_TEST(test_get_option_none);
    return UNITY_END();
}

