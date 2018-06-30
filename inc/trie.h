#pragma once
#define CHARSET 36  //numbers + characters 

typedef struct TrieNode {
    struct TrieNode *next[CHARSET]; // One son for every character
    unsigned int occurrencies;
} TrieNode;

TrieNode *create_trie ( void );
void insert(TrieNode *, char *);