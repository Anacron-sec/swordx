#pragma once
#define CHARSET 36  // 10 digits + 26 alphabet

typedef struct TrieNode {
    struct TrieNode *next[CHARSET];
    unsigned int occurrencies;
} TrieNode;

TrieNode *create_trie ( void );
void trie_insert(TrieNode *, char *);