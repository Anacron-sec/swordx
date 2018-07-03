#include <stdlib.h>
#include <stdio.h>
#include "trie.h"
#include "utils.h"

static void init_node(TrieNode*);
static void attach_new_node(TrieNode*, short);

TrieNode *create_trie() {
    TrieNode *trie = (TrieNode*) malloc(sizeof(TrieNode)); check_heap(trie);
    init_node(trie);

    return trie;
}

void trie_insert(TrieNode *trie, char* new_string) {
    TrieNode *tmp_node = trie; 
    char *query_next = new_string;
    int next_position = 0;

    while(*query_next != '\0') {
        next_position = map_char(*query_next);
        if(tmp_node->next[next_position] == NULL)
            attach_new_node(tmp_node, next_position);
        
        /* move to the next char in both trie and new string */
        tmp_node = tmp_node->next[next_position];
        query_next++;
    }
    tmp_node->occurrencies++;
}

static void init_node(TrieNode* node) {
    node->occurrencies = 0;
    for(int i = 0; i < CHARSET; i++){
        node->next[i] = NULL;
    }
}

static void attach_new_node(TrieNode* node, short position) {
    TrieNode *new_node = (TrieNode*) malloc(sizeof(TrieNode)); check_heap(new_node);
    init_node(new_node);
    node->next[position] = new_node;
}