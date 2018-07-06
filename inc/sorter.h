#pragma once
#include <stdlib.h>

/* First-class ADT, wordWithOccurrences is defined in implementation */
typedef struct wordWithOccurrences* wordWithOccurrencesPtr;

/* Create a new wordWithOccurrences Structure 
** char* is the word
** int is the number of occurences
*/
wordWithOccurrencesPtr create_wordWithOccurrences(char*, int);

/*
** Frees up memory
*/
void destroy_wordWithOccurrences(wordWithOccurrencesPtr);

/*
** Sorts an array of pointers to wordWithOccurrencesPtr
** size_t is the size of the array
*/
void sort_words_by_occurrences(wordWithOccurrencesPtr[], size_t);

/* Returns the word inside of a target wordWithOccurrences */
char* get_word(wordWithOccurrencesPtr);

/* Returns the number of occurences of a target wordWithOccurrences */
int get_occurrences(wordWithOccurrencesPtr);