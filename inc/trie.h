#pragma once
#define CHARSET 36  // 10 digits + 26 alphabet

/* W_DUP stands for word duplicate, W_NEW stands for word new */
typedef enum {WORD_DUPLICATE, WORD_NEW} wordStatus;

typedef struct TrieNode {
    struct TrieNode *next[CHARSET];
    int occurrences;
    char* target_word;
} TrieNode;

/* Initializes a trie and returns a pointer to the new structure */
TrieNode *create_trie (void);

/* Inserts target word into the specified trie 
** Returns W_DUP if the word already exists, W_NEW otherwise
*/
wordStatus trie_insert(TrieNode *, char *);

/* callback is a user defined function that's called at every word*/
void trie_process_words (TrieNode*, void (*)(char*, int));