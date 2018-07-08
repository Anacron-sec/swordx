#pragma once

#include <stdlib.h>
#include "word_utils.h"

typedef enum {ERROR_INSERT = -1, OK_INSERT} insertStatus;

/* First-class ADT, Trie is defined in implementation */
typedef struct Trie* TriePtr;

/* Initializes a trie and returns a pointer to the new structure */
TriePtr create_trie (void);

/* Frees up memory */
void destroy_trie(TriePtr);

/* Inserts target word into the specified trie
*/
insertStatus trie_insert(TriePtr, char *);

/* Returns the number of unique words inside the trie */
size_t get_count(TriePtr);

/* Returns a wordWithOccurences array */
WordWithOccurrencesPtr* sort_trie_by_occurences(TriePtr);