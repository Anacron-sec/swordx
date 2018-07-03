#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

    /* If the word is new, allocates space for the new string and stores it setti */
    if(tmp_node->target_word == NULL) {
        tmp_node->target_word = malloc(strlen(new_string) * sizeof(char)); 
        check_heap(tmp_node->target_word);
        strcpy(tmp_node->target_word, new_string);
    }

    /* Increase occurencies in every case */
    tmp_node->occurrencies++;
}

void trie_process_words (TrieNode* trie, void (*callback)(char*, int)) {
    /*
    if(trie->occurrencies > 0)
        callback(word, occurencies);
    for(int i = 0; i < CHARSET; i++) {
        if(trie->next[i] != NULL)
            trie_process_words(trie->next[i], callback);
    }
    */
}

static void init_node(TrieNode* node) {
    node->occurrencies = 0;
    node->target_word = NULL;
    for(int i = 0; i < CHARSET; i++){
        node->next[i] = NULL;
    }
}

static void attach_new_node(TrieNode* node, short position) {
    TrieNode *new_node = (TrieNode*) malloc(sizeof(TrieNode)); check_heap(new_node);
    init_node(new_node);
    node->next[position] = new_node;
}