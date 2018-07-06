#pragma once

/* W_DUP stands for word duplicate, W_NEW stands for word new */
typedef enum {WORD_NEW, WORD_DUPLICATE} wordStatus;

/* First-class ADT, TrieNode is defined in implementation */
typedef struct TrieNode* TrieNodePtr;

/* Initializes a trie and returns a pointer to the new structure */
TrieNodePtr create_trie (void);

/* Inserts target word into the specified trie 
** Returns WORD_DUPLICATE if the word already exists, WORD_NEW otherwise
*/
wordStatus trie_insert(TrieNodePtr, char *);

/* callback is a user defined function that's called at every word*/
void trie_process_words (TrieNodePtr, void (*)(char*, int));