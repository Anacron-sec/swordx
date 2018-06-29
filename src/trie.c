#include <stdlib.h>
#include "trie.h"

trie_node_t *create_trie() {
    trie_node_t *trie = (trie_node_t*) malloc(sizeof(trie_node_t));
    if(trie == NULL) {
        perror("Out of memory");
        exit(EXIT_FAILURE);
    }
    trie->occurrencies = 0;
    for(int i = 0; i < CHARSET; i++){
        trie->next[i] = NULL;
    }
    return trie;
}

void insert(trie_node_t *trie, char* new_string) {
    trie_node_t *tmp_node, *new_node;
    char *query_next;
    tmp_node = trie; query_next = new_string;
    while(*query_next != '\0') {
        if(tmp_node->next[(int) (*query_next)] == NULL) {
            new_node = (trie_node_t*) malloc(sizeof(trie_node_t));
            if(new_node == NULL) {
                perror("Out of memory");
                exit(EXIT_FAILURE);
            }
            new_node->occurrencies = 0;
            for(int i = 0; i < CHARSET; i++){
                new_node->next[i] = NULL;
            }
            tmp_node->next[(int)(*query_next)] = new_node;
        }
        /* move to next char in both trie and new string */
        tmp_node = tmp_node->next[(int)(*query_next)];
        query_next++;
    }
    /* check if string exists and increase occurrencies, otherwise create it*/
    if( tmp_node->next[(int)'\0'] != NULL ) tmp_node->next[(int)'\0']->occurrencies++;
    else {
        trie_node_t *word;
        word = (trie_node_t*) malloc(sizeof(trie_node_t));
        word->occurrencies = 1;
        tmp_node->next[(int)'\0'] = word;
    }
}

//TODO enum for alphabet with non-english char or something similar
//TODO use a string in the '\0' node or a find a better solution
//TODO modify query_next++ to be able to be used with non-english char

