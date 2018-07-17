#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "trie.h"
#include "utils.h"
#include "word_utils.h"

#define CHARSET 36 // 10 digits + 26 alphabets

static const char BASE_DIGIT = '0';
static const char BASE_CHAR = 'a';
static const int CHAR_OFFSET = 10;

bool alpha = false;
long int min_chars = 0;
char** word_blacklist = NULL;
size_t word_blacklist_size = 0;

struct TrieNode {
    struct TrieNode *next[CHARSET];
    int occurrences;
    char* stored_word;
};

struct Trie {
    struct TrieNode *root_node;
    size_t word_count;
};

static int map_char(char c);
static void init_node(struct TrieNode*);
static void attach_new_node(struct TrieNode*, short);
static void destroy_trie_nodes(struct TrieNode*);
static void trie_to_WordWithOccurences_array(struct TrieNode*, WordWithOccurrencesPtr*, int*);
static WordWithOccurrencesPtr* sort_trie_by_occurences(TriePtr);
static void write_words_to_file(struct TrieNode*, FILE*);

TriePtr create_trie() {
    TriePtr trie = (TriePtr) malloc(sizeof(struct Trie)); check_heap(trie);

    struct TrieNode* node = (struct TrieNode*) malloc(sizeof(struct TrieNode)); check_heap(node);
    init_node(node);

    trie->root_node = node;
    trie->word_count = 0;

    return trie;
}

void destroy_trie(TriePtr trie) {
    destroy_trie_nodes(trie->root_node);
    free(trie);
}

insertStatus trie_insert(TriePtr trie, char* new_string) {

    // Checks if the word is blacklisted.
    for(int i = 0; i < word_blacklist_size; i++) {
        if(strcmp(word_blacklist[i],new_string) == 0) return ERROR_INSERT;
    }

    if(min_chars != 0 && strlen(new_string) < min_chars)
        return ERROR_INSERT;

    struct TrieNode *tmp_node = trie->root_node;
    char *query_next = new_string;
    int next_position = 0;

    while(*query_next != '\0') {
        next_position = map_char(*query_next);

        /* checks if alpha are allowed */
        if(next_position >= 0 && next_position <= 9 && alpha == true) {
            return ERROR_INSERT;
        } //TODO: Clean tree or check before

        /* If not a word return error */
        if(next_position == -1) return ERROR_INSERT; //TODO: Clean tree or check before
        if(tmp_node->next[next_position] == NULL)
            attach_new_node(tmp_node, next_position);
        
        /* move to the next char in both trie and new string */
        tmp_node = tmp_node->next[next_position];
        query_next++;
    }
    
    if(tmp_node->stored_word == NULL) {
        tmp_node->stored_word = malloc(strlen(new_string) * sizeof(char)); check_heap(tmp_node->stored_word);
        strcpy(tmp_node->stored_word, new_string);
        trie->word_count++;
    }

    /* Increase occurences in every case */
    tmp_node->occurrences++;
    return OK_INSERT;
}

size_t get_count(TriePtr trie) {
    return trie->word_count;
}

writeStatus write_trie(TriePtr trie, char *file_name) {
    FILE *fptr = fopen(file_name,"w");
    
    if(fptr == NULL)
        return ERROR_WRITE;

    write_words_to_file(trie->root_node, fptr);
    fclose(fptr);
    return OK_WRITE;
}

writeStatus write_trie_by_occurrences(TriePtr trie, char *file_name) {
    FILE *fptr = fopen(file_name, "w");
    
    if(fptr == NULL)
        return ERROR_WRITE;

    WordWithOccurrencesPtr* wwo_ptr = sort_trie_by_occurences(trie);
    for(int i=0; i < trie->word_count; i++) {
        fprintf(fptr, "%s %d\n", get_word(wwo_ptr[i]), get_occurrences(wwo_ptr[i]));
    }
    fclose(fptr);
    free(wwo_ptr);
    return OK_WRITE;
}

bulkInsertStatus trie_bulk_insert(TriePtr trie, char *file_name) {
    FILE *fptr = fopen(file_name, "r");
    if(fptr == NULL) {
        return ERROR_BULK;
    }

    char * line = NULL;
    size_t len = 0;
    while(getline(&line, &len, fptr) != -1) {
        char* token;
        char* save;

        if(line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0'; // Strips \n from line

        token = strtok_r(line, " ", &save);

        while(token != NULL) {
            trie_insert(trie, token);
            token = strtok_r(NULL, " ", &save);
        }
    }
    fclose(fptr);

    return OK_BULK;
}


static void write_words_to_file(struct TrieNode* node, FILE* file_pointer) {
    if (node->occurrences > 0)
        fprintf(file_pointer,"%s %d\n",node->stored_word, node->occurrences);

    // Recursively calls for entire trie
    for (int i = 0; i < CHARSET; i++) {
        if(node->next[i] != NULL) write_words_to_file(node->next[i], file_pointer);
    }
}

static WordWithOccurrencesPtr* sort_trie_by_occurences(TriePtr trie) {
    size_t size = trie->word_count;
    WordWithOccurrencesPtr* words = (WordWithOccurrencesPtr*) malloc(size * sizeof(WordWithOccurrencesPtr)); check_heap(words);

    int counter = 0; int* counter_ptr = &counter;

    trie_to_WordWithOccurences_array(trie->root_node, words, counter_ptr);

    sort_words_by_occurrences(words, size);

    return words;
}

static void init_node(struct TrieNode* node) {
    node->occurrences = 0;
    node->stored_word = NULL;
    for(int i = 0; i < CHARSET; i++){
        node->next[i] = NULL;
    }
}

static void attach_new_node(struct TrieNode* node, short position) {
    struct TrieNode *new_node = (struct TrieNode*) malloc(sizeof(struct TrieNode)); check_heap(new_node);
    init_node(new_node);
    node->next[position] = new_node;
}

static int map_char(char c) {
    if(isdigit(c)) 
        return (c - BASE_DIGIT);

    char lowercase = tolower(c);

    return islower(lowercase) ? (lowercase - BASE_CHAR + CHAR_OFFSET) : -1;
}

static void destroy_trie_nodes(struct TrieNode* trie_node) {

    for(int i = 0; i < CHARSET; i++) {
        if(trie_node->next[i] != NULL)
            destroy_trie_nodes(trie_node->next[i]);
    }
    free(trie_node);
}

static void trie_to_WordWithOccurences_array(struct TrieNode* trie_node, WordWithOccurrencesPtr* wwo, int* counter) {
    if(trie_node->occurrences > 0) {
        wwo[*counter] = create_WordWithOccurrences(trie_node->stored_word, trie_node->occurrences);
        *counter = *counter + 1;
    }

    for (int i = 0; i < CHARSET; i++) {
        if(trie_node->next[i] != NULL)
            trie_to_WordWithOccurences_array(trie_node->next[i], wwo, counter);
    }
}