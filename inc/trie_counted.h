#pragma once
#include "trie.h"

typedef struct TrieWithCounter {
    TrieNodePtr trie;
    unsigned long long counter;
} TrieWithCounter;

/* Initializes a trie and returns a pointer to the new structure */
TrieWithCounter* create_trie_c (void);

/* Inserts target word into the specified trie 
** Increases counter if the word is new.
*/
void trie_c_insert(TrieWithCounter *, char *);