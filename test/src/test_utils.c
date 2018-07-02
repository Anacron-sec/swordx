#include <CUnit/CUnit.h>
#include "utils.h"
#include "test_utils.h"

int init_suite_utils(void) { return 0; }
int clean_suite_utils(void) { return 0; }

void test_map_char_alphabet (void) {
    for (int i = 0; i < 26; i++) {
        CU_ASSERT_EQUAL(map_char('a' + i), (i + 10));
    }
}

void test_map_char_digits (void) {
    for (int i = 0; i < 10; i++) {
        CU_ASSERT_EQUAL(map_char('0' + i), i);
    }
}

void test_map_char_nul (void) {
    CU_ASSERT_EQUAL(map_char('\0'), 36);
}

void test_map_char_uppercase (void) {
    for (int i = 0; i < 26; i++) {
        CU_ASSERT_EQUAL(map_char('A' + i), (i + 10));
    }
}
