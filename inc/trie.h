#pragma once

#include <stdlib.h>
#include "sorter.h"


/* First-class ADT, Trie is defined in implementation */
typedef struct Trie* TriePtr;

/* Initializes a trie and returns a pointer to the new structure */
TriePtr create_trie (void);

/* Frees up memory */
void destroy_trie(TriePtr);

/* Inserts target word into the specified trie
*/
void trie_insert(TriePtr, char *);

/* Returns the number of unique words inside the trie */
size_t get_count(TriePtr);

/* Returns a wordWithOccurences array */
wordWithOccurrencesPtr* sort_trie_by_occurences(TriePtr);