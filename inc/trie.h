#pragma once
#define CHARSET 36  // 10 digits + 26 alphabet

typedef struct TrieNode {
    struct TrieNode *next[CHARSET];
    unsigned int occurrencies;
    char* target_word;
} TrieNode;

/* Initializes a trie and returns a pointer to the new structure */
TrieNode *create_trie (void);

/* Inserts target word into the specified trie */
void trie_insert(TrieNode *, char *);

/* callback is a user defined function that's called at every word*/
void trie_process_words (TrieNode*, void (*)(char*, int));