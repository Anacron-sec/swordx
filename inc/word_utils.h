#pragma once
#include <stdlib.h>

/* First-class ADT, WordWithOccurrences is defined in implementation */
typedef struct WordWithOccurrences* WordWithOccurrencesPtr;

/* Create a new WordWithOccurrences Structure 
** char* is the word
** int is the number of occurences
*/
WordWithOccurrencesPtr create_WordWithOccurrences(char*, int);

/*
** Frees up memory
*/
void destroy_WordWithOccurrences(WordWithOccurrencesPtr);

/*
** Sorts an array of pointers to WordWithOccurrencesPtr
** size_t is the size of the array
*/
void sort_words_by_occurrences(WordWithOccurrencesPtr*, size_t);

/* Returns the word inside of a target WordWithOccurrences */
char* get_word(WordWithOccurrencesPtr);

/* Returns the number of occurences of a target WordWithOccurrences */
int get_occurrences(WordWithOccurrencesPtr);