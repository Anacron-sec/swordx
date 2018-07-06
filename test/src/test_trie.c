#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <string.h>
#include "test_trie.h"
#include "trie.h"
#include "utils.h"

TrieNodePtr test_trie;

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

static char words[2][500];
static int occs[2];

static void process_words(char* wordFound, int occ) {
    static int i = 0;
    strcpy(words[i], wordFound);
    occs[i] = occ;
    i++;
}

void test_process_function (void) {
    trie_process_words(test_trie, process_words);
    CU_ASSERT_STRING_EQUAL(words[0], "wordone");
    CU_ASSERT_STRING_EQUAL(words[1], "wordtwo");
    CU_ASSERT_EQUAL(occs[0], 1);
    CU_ASSERT_EQUAL(occs[1], 2);
}