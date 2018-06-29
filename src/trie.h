#pragma once
#define CHARSET 256

typedef struct trie_n_t {
    struct trie_n_t *next[CHARSET];
    unsigned int occurrencies;
} trie_node_t;

trie_node_t *create_trie ( void );
void insert(trie_node_t *, char *);