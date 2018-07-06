#include <stdlib.h>
#include "trie.h"
#include "trie_counted.h"
#include "utils.h"

struct TrieWithCounter {
    TrieNodePtr trie;
    unsigned long long counter;
};

TrieWithCounterPtr create_trie_c (void) {
        TrieWithCounterPtr trie_c = (TrieWithCounterPtr) malloc(sizeof(struct TrieWithCounter)); check_heap(trie_c);
        trie_c->trie = create_trie();
        trie_c->counter = 0;

        return trie_c;
}

void trie_c_insert(TrieWithCounterPtr trie_c, char * target_word) {
    if(trie_insert(trie_c->trie, target_word) == WORD_NEW) 
        trie_c->counter++;
}

TrieNodePtr get_trie(TrieWithCounterPtr trie_c) {
        return trie_c->trie;
}

int get_count(TrieWithCounterPtr trie_c) {
        return trie_c->counter;
}