#include <stdlib.h>
#include <CUnit/CUnit.h>
#include "test_trie_c.h"
#include "trie_c.h"

TrieWithCounter* test_trie_c;

int init_suite_trie_c(void) {
    test_trie_c = create_trie_c();
    return 0;
}

int clean_suite_trie_c(void) { 
    free(test_trie_c);
    return 0;
}

void test_create_trie_c (void) {
    CU_ASSERT_PTR_NOT_NULL_FATAL(test_trie_c->trie);
    CU_ASSERT_EQUAL(test_trie_c->counter, 0);
}

void test_insert_new_word (void) {
    char* testword = "testword";
    trie_c_insert(test_trie_c, testword);
    CU_ASSERT_EQUAL(test_trie_c->counter, 1);
}

void test_insert_dup_word (void) {
    char* testword = "testword";
    trie_c_insert(test_trie_c, testword);
    CU_ASSERT_EQUAL(test_trie_c->counter, 1);
}



