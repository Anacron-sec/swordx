#include <stdlib.h>
#include "trie.h"
#include "trie_c.h"
#include "utils.h"

TrieWithCounter *create_trie_c (void) {
        TrieWithCounter *trie_c = (TrieWithCounter*) malloc(sizeof(TrieWithCounter)); check_heap(trie_c);
        trie_c->trie = create_trie();
        trie_c->counter = 0;

        return trie_c;
}

void trie_c_insert(TrieWithCounter * trie_c, char * target_word){
    if( trie_insert(trie_c->trie, target_word) == W_NEW) trie_c->counter++;
}