#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "trie.h"
#include "utils.h"

#define CHARSET 36 // 10 digits + 26 alphabets

static const char BASE_DIGIT = '0';
static const char BASE_CHAR = 'a';
static const int CHAR_OFFSET = 10;

struct TrieNode {
    struct TrieNode *next[CHARSET];
    int occurrences;
    char* target_word;
};

static int map_char(char c);
static void init_node(TrieNodePtr);
static void attach_new_node(TrieNodePtr, short);

TrieNodePtr create_trie() {
    TrieNodePtr trie = (TrieNodePtr) malloc(sizeof(struct TrieNode)); check_heap(trie);
    init_node(trie);

    return trie;
}

void destroy_trie(TrieNodePtr trie) {
    for(int i = 0; i < CHARSET; i++) {
        if(trie->next[i] != NULL)
            destroy_trie(trie->next[i]);
    }
    free(trie);
}

wordStatus trie_insert(TrieNodePtr trie, char* new_string) {
    
    struct TrieNode *tmp_node = trie; 
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
    wordStatus status;
    
    if(tmp_node->target_word == NULL) {
        tmp_node->target_word = malloc(strlen(new_string) * sizeof(char)); check_heap(tmp_node->target_word);
        strcpy(tmp_node->target_word, new_string);
        status = WORD_NEW;
    } else {
        status = WORD_DUPLICATE;
    }

    /* Increase occurences in every case */
    tmp_node->occurrences++;
    return status;
}

void trie_process_words (TrieNodePtr node, void (*process_function)(char*, int)) {    
    if(node->occurrences > 0){
        process_function(node->target_word, node->occurrences);
    }

    for(int i = 0; i < CHARSET; i++) {
        if(node->next[i] != NULL)
            trie_process_words(node->next[i], process_function);
    }
}

static void init_node(TrieNodePtr node) {
    node->occurrences = 0;
    node->target_word = NULL;
    for(int i = 0; i < CHARSET; i++){
        node->next[i] = NULL;
    }
}

static void attach_new_node(TrieNodePtr node, short position) {
    struct TrieNode *new_node = (TrieNodePtr) malloc(sizeof(struct TrieNode)); check_heap(new_node);
    init_node(new_node);
    node->next[position] = new_node;
}

static int map_char(char c) {
    if(isdigit(c)) 
        return (c - BASE_DIGIT);

    char lowercase = tolower(c);

    return islower(lowercase) ? (lowercase - BASE_CHAR + CHAR_OFFSET) : -1;
}