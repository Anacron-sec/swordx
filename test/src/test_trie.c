#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <string.h>
#include "test_trie.h"
#include "trie.h"
#include "utils.h"

TrieNode* test_trie;

int init_suite_trie(void) {
    test_trie = create_trie();
    return 0;
}

int clean_suite_trie(void) { 
    free(test_trie);
    return 0;
}

void test_create_trie (void) {
    CU_ASSERT_PTR_NOT_NULL(test_trie);
    CU_ASSERT_EQUAL(test_trie->occurrencies, 0);
    for(int i=0; i < CHARSET; i++) {
        CU_ASSERT_PTR_NULL(test_trie->next[i]);
    }
}

void test_insert_single_word (void) {
    TrieNode* tmp_node;
    char* word = "testword";
    trie_insert(test_trie, word);
    tmp_node = test_trie;
    for(int i = 0; i < strlen(word); i++) {
        CU_ASSERT_PTR_NOT_NULL_FATAL(tmp_node = tmp_node->next[map_char(word[i])]);
    }
    CU_ASSERT_EQUAL(tmp_node->occurrencies, 1);
}

void test_insert_multiple_words (void) {
    TrieNode* tmp_node;
    char* word = "testword";
    /* Add test word another 3 times */
    for (int i = 0; i < 3; i++) {
        trie_insert(test_trie, word);
    }
    tmp_node = test_trie;
    for(int i = 0; i < strlen(word); i++) {
        CU_ASSERT_PTR_NOT_NULL_FATAL(tmp_node = tmp_node->next[map_char(word[i])]);
    }
    /* 1 from the previous test + 3 of this  = 4*/
    CU_ASSERT_EQUAL(tmp_node->occurrencies, 4);
}

void test_insert_different_words (void) {
    TrieNode* tmp_node;
    char* previousword = "testword";
    char* word = "testwordtwo";
    trie_insert(test_trie, word);
    tmp_node = test_trie;

    /* Tests current word with occurrency 1 */
    for(int i = 0; i < strlen(word); i++) {
        CU_ASSERT_PTR_NOT_NULL_FATAL(tmp_node = tmp_node->next[map_char(word[i])]);
    }
    CU_ASSERT_EQUAL(tmp_node->occurrencies, 1);
    tmp_node = test_trie;
    
    /* Tests previous word to still be of occurrency 4 */
    for(int i = 0; i < strlen(previousword); i++) {
        CU_ASSERT_PTR_NOT_NULL_FATAL(tmp_node = tmp_node->next[map_char(word[i])]);
    }
    CU_ASSERT_EQUAL(tmp_node->occurrencies, 4);
}