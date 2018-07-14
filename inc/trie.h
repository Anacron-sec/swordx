#pragma once

#include <stdlib.h>

typedef enum {ERROR_INSERT = -1, OK_INSERT} insertStatus;
typedef enum {ERROR_WRITE = -1, OK_WRITE} writeStatus;
typedef enum {ERROR_BULK = -1, OK_BULK} bulkInsertStatus;

/* First-class ADT, Trie is defined in implementation */
typedef struct Trie* TriePtr;

/* Initializes a trie and returns a pointer to the new structure */
TriePtr create_trie (void);

/* Frees up memory */
void destroy_trie(TriePtr);

/* Inserts target word into the specified trie
*/
insertStatus trie_insert(TriePtr, char *);

/* Inserts words directly from a file */
bulkInsertStatus trie_bulk_insert(TriePtr, char *);

/* Returns the number of unique words inside the trie */
size_t get_count(TriePtr);

/* Writes the entire trie to the disk */
writeStatus write_trie(TriePtr, char *);

/* Writes the entire trie to the disk sorted by occurences */
writeStatus write_trie_by_occurrences(TriePtr, char *);
