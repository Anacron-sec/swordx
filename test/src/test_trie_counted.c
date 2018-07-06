#include <stdlib.h>
#include <CUnit/CUnit.h>
#include "test_trie_counted.h"
#include "trie_counted.h"

TrieWithCounterPtr test_trie_c;

int init_suite_trie_c(void) {
    test_trie_c = create_trie_c();
    return 0;
}

int clean_suite_trie_c(void) { 
    destroy_trie_c(test_trie_c);
    return 0;
}

void test_create_trie_c (void) {
    CU_ASSERT_PTR_NOT_NULL_FATAL(get_trie(test_trie_c));
    CU_ASSERT_EQUAL(get_count(test_trie_c), 0);
}

void test_insert_new_word (void) {
    char* testword = "testword";
    trie_c_insert(test_trie_c, testword);
    CU_ASSERT_EQUAL(get_count(test_trie_c), 1);
}

/* Repeating the same test should lead to the counter not increased as testword is the same */
void test_insert_dup_word (void) {
    char* testword = "testword";
    trie_c_insert(test_trie_c, testword);
    CU_ASSERT_EQUAL(get_count(test_trie_c), 1);
}



