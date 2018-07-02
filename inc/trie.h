#pragma once
#define CHARSET 37  // 10 digits + 26 alphabet + nul

typedef struct TrieNode {
    struct TrieNode *next[CHARSET];
    unsigned int occurrencies;
} TrieNode;

TrieNode *create_trie ( void );
void trie_insert(TrieNode *, char *);