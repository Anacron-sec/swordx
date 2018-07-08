#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <string.h>
#include "test_trie.h"
#include "trie.h"
#include "word_utils.h"
#include "utils.h"

TriePtr test_trie;

int init_suite_trie(void) {
    test_trie = create_trie();
    return 0;
}

int clean_suite_trie(void) { 
    destroy_trie(test_trie);
    return 0;
}

void test_create_trie (void) {
    CU_ASSERT_PTR_NOT_NULL(test_trie);
}

void test_insert_trie (void) {
    CU_ASSERT_EQUAL(OK_INSERT, trie_insert(test_trie, "one"));
    CU_ASSERT_EQUAL(ERROR_INSERT, trie_insert(test_trie, "!?=blah"));
}

void test_get_count(void) {
    
    for(int i = 0; i < 2; i++) {
        trie_insert(test_trie, "two");
    }

    for(int i = 0; i < 3; i++) {
        trie_insert(test_trie, "three");
    }

    for(int i=0; i < 100; i++) {
        trie_insert(test_trie, "hundred");
    }

    for(int i=0; i < 1000; i++) {
        trie_insert(test_trie, "thousand");
    }

    CU_ASSERT_EQUAL(get_count(test_trie), 5);
}

void test_sort(void) {
    WordWithOccurrencesPtr* sorted_trie = sort_trie_by_occurences(test_trie);
    CU_ASSERT_PTR_NOT_NULL(sorted_trie);

    CU_ASSERT_STRING_EQUAL(get_word(sorted_trie[0]), "thousand");
    CU_ASSERT_EQUAL(get_occurrences(sorted_trie[0]), 1000);
    CU_ASSERT_STRING_EQUAL(get_word(sorted_trie[1]), "hundred");
    CU_ASSERT_EQUAL(get_occurrences(sorted_trie[1]), 100);
    CU_ASSERT_STRING_EQUAL(get_word(sorted_trie[2]), "three");
    CU_ASSERT_EQUAL(get_occurrences(sorted_trie[2]), 3);
    CU_ASSERT_STRING_EQUAL(get_word(sorted_trie[3]), "two");
    CU_ASSERT_EQUAL(get_occurrences(sorted_trie[3]), 2);
    CU_ASSERT_STRING_EQUAL(get_word(sorted_trie[4]), "one");
    CU_ASSERT_EQUAL(get_occurrences(sorted_trie[4]), 1);

    free(sorted_trie);
}