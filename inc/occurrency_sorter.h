#pragma once

typedef struct wordWithOccurrency* wordWithOccurrencyPtr;

wordWithOccurrencyPtr create_wordWithOccurrency(char*, int);

void sort_words_by_occurrency(wordWithOccurrencyPtr[], size_t);

char* get_word(wordWithOccurrencyPtr);
int get_occurences(wordWithOccurrencyPtr);