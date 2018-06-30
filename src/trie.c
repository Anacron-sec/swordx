#include <stdlib.h>
#include <stdio.h>
#include "trie.h"
#include "utils.h"

TrieNode *create_trie() {
    TrieNode *trie = (TrieNode*) malloc(sizeof(TrieNode)); check_heap(trie);
    trie->occurrencies = 0;
    for(int i = 0; i < CHARSET; i++){
        trie->next[i] = NULL;
    }
    return trie;
}

void insert(TrieNode *trie, char* new_string) {
    TrieNode *tmp_node, *new_node;
    char *query_next;
    tmp_node = trie; query_next = new_string;
    while(*query_next != '\0') {
        if(tmp_node->next[map_char(*query_next)] == NULL) {
            new_node = (TrieNode*) malloc(sizeof(TrieNode)); check_heap(new_node);
            new_node->occurrencies = 0;
            for(int i = 0; i < CHARSET; i++){
                new_node->next[i] = NULL;
            }
            tmp_node->next[map_char(*query_next)] = new_node;
        }
        /* move to next char in both trie and new string */
        tmp_node = tmp_node->next[(int)(*query_next)];
        query_next++;
    }
    /* check if string exists and increase occurrencies, otherwise create it*/
    if( tmp_node->next[(int)'\0'] != NULL ) tmp_node->next[(int)'\0']->occurrencies++;
    else {
        TrieNode *word;
        word = (TrieNode*) malloc(sizeof(TrieNode)); check_heap(word);
        word->occurrencies = 1;
        tmp_node->next[(int)'\0'] = word;
    }
}
