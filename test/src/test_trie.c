#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <string.h>
#include <stdio.h>
#include "test_trie.h"
#include "trie.h"
//#include "word_utils.h"
#include "utils.h"

TriePtr test_trie;
char test_words[5][100];
int occurrences[5];

int init_suite_trie(void) {
    test_trie = create_trie();
    strcpy(test_words[0], "one");
    strcpy(test_words[1], "two");
    strcpy(test_words[2], "three");
    strcpy(test_words[3], "hundred");
    strcpy(test_words[4], "thousand");
    occurrences[0] = 1;
    occurrences[1] = 2;
    occurrences[2] = 3;
    occurrences[3] = 100;
    occurrences[4] = 1000;

    return 0;
}

int clean_suite_trie(void) { 
    destroy_trie(test_trie);
    return 0;
}

void test_create_trie (void) {
    CU_ASSERT_PTR_NOT_NULL_FATAL(test_trie);
}

void test_insert_trie (void) {
    CU_ASSERT_EQUAL_FATAL(OK_INSERT, trie_insert(test_trie, test_words[0]));
    CU_ASSERT_EQUAL_FATAL(ERROR_INSERT, trie_insert(test_trie, "!?=blah"));
}

void test_get_count(void) {
    
    for(int i = 0; i < occurrences[1]; i++) {
        trie_insert(test_trie, test_words[1]);
    }

    for(int i = 0; i < occurrences[2]; i++) {
        trie_insert(test_trie, test_words[2]);
    }

    for(int i=0; i < occurrences[3]; i++) {
        trie_insert(test_trie, test_words[3]);
    }

    for(int i=0; i < occurrences[4]; i++) {
        trie_insert(test_trie, test_words[4]);
    }

    CU_ASSERT_EQUAL_FATAL(get_count(test_trie), 5);
}

void test_write_trie(void) {
    // Words are printed alphabetically
    int new_order[5] = {3, 0, 4, 2, 1};
    writeStatus ws = write_trie(test_trie, "result.txt");
    CU_ASSERT_EQUAL(ws, OK_WRITE);

    FILE *fptr = fopen("result.txt", "r");
    CU_ASSERT_PTR_NOT_NULL_FATAL(fptr);

    for(int i=0; i < get_count(test_trie); i++) {
        char * line = NULL;
        size_t len = 0;
        CU_ASSERT_NOT_EQUAL_FATAL(getline(&line, &len, fptr), -1);
        char cmp[100];
        sprintf(cmp, "%s %d\n", test_words[new_order[i]], occurrences[new_order[i]]);
        CU_ASSERT_STRING_EQUAL(line, cmp);
        free(line);
    }
    fclose(fptr);
    CU_ASSERT_EQUAL(remove("result.txt"), 0);
}

/*
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
*/