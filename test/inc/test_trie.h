#pragma once

int init_suite_trie(void);
int clean_suite_trie(void);

void test_create_trie (void);
void test_insert_single_word(void);
void test_insert_multiple_words (void);
void test_insert_different_words (void);
void test_process_words (void);