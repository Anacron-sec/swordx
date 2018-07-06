#pragma once
#include "trie.h"

/* First-class ADT, TrieWithCounter is defined in implementation */
typedef struct TrieWithCounter* TrieWithCounterPtr;

/* Initializes a trie and returns a pointer to the new structure */
TrieWithCounterPtr create_trie_c (void);

/* Frees up memory */
void destroy_trie_c (TrieWithCounterPtr);

/* Inserts target word into the specified trie 
** Increases counter if the word is new.
*/
void trie_c_insert(TrieWithCounterPtr, char *);

/* Returns the trie that is contained inside the trie with counter */
TrieNodePtr get_trie(TrieWithCounterPtr);

/* Returns the number of unique words inside the trie */
int get_count(TrieWithCounterPtr);