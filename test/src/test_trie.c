#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <string.h>
#include "test_trie.h"
#include "trie.h"
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

void test_get_count(void) {
    trie_insert(test_trie, "one");
    
    for(int i = 0; i < 5; i++) {
        trie_insert(test_trie, "two");
    }

    trie_insert(test_trie, "three");
    trie_insert(test_trie, "three");

    CU_ASSERT_EQUAL(get_count(test_trie), 3);
}

/*
void test_insert_word (void) {
    char *wordToInsert = "wordtwo";
    wordStatus ws = trie_insert(test_trie, wordToInsert);
    CU_ASSERT_EQUAL(ws, WORD_NEW);

    ws = trie_insert(test_trie, wordToInsert);
    CU_ASSERT_NOT_EQUAL(ws, WORD_NEW);
    CU_ASSERT_EQUAL(ws, WORD_DUPLICATE);

    char *newWord = "wordone";
    ws = trie_insert(test_trie, newWord);
    CU_ASSERT_EQUAL(ws, WORD_NEW);
}
*/