#pragma once

/* First-class ADT, wordWithOccurrency is defined in implementation */

typedef struct wordWithOccurrency* wordWithOccurrencyPtr;

/* Create a new wordWithOccurrency Structure 
** char* is the word
** int is the number of occurences
*/
wordWithOccurrencyPtr create_wordWithOccurrency(char*, int);

/*
** Sorts an array of pointers to wordWithOccurrencyPtr
** size_t is the size of the array
*/
void sort_words_by_occurrency(wordWithOccurrencyPtr[], size_t);

/* Returns the word inside of a target wordWithOccurrency */
char* get_word(wordWithOccurrencyPtr);

/* Returns the number of occurences of a target wordWithOccurrency */
int get_occurrences(wordWithOccurrencyPtr);