#pragma once

int init_suite_trie(void);
int clean_suite_trie(void);

void test_create_trie (void);
void test_insert_trie (void);
void test_get_count(void);
void test_write_trie(void);
void test_write_trie_sorted(void);
void test_trie_bulk_insert(void);

//void test_sort(void);