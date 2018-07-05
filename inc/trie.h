#pragma once

/* W_DUP stands for word duplicate, W_NEW stands for word new */
typedef enum {WORD_DUPLICATE, WORD_NEW} wordStatus;

typedef struct TrieNode* TrieNodePtr;

/* Initializes a trie and returns a pointer to the new structure */
TrieNodePtr create_trie (void);

/* Inserts target word into the specified trie 
** Returns W_DUP if the word already exists, W_NEW otherwise
*/
wordStatus trie_insert(TrieNodePtr, char *);

/* callback is a user defined function that's called at every word*/
void trie_process_words (TrieNodePtr, void (*)(char*, int));