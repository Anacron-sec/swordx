#pragma once
#define CHARSET 36  // 10 digits + 26 alphabet

typedef enum {W_DUP, W_NEW} w_stat;

typedef struct TrieNode {
    struct TrieNode *next[CHARSET];
    unsigned int occurrences;
    char* target_word;
} TrieNode;

/* Initializes a trie and returns a pointer to the new structure */
TrieNode *create_trie (void);

/* Inserts target word into the specified trie 
** Returns -1 if it had problems,  
*/
w_stat trie_insert(TrieNode *, char *);

/* callback is a user defined function that's called at every word*/
void trie_process_words (TrieNode*, void (*)(char*, int));