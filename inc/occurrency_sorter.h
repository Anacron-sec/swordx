#pragma once

typedef struct wordWithOccurrency {
    char* word_chosen;
    int occurences;
} wordWithOccurrency;

wordWithOccurrency* create_wordWithOccurrency(char*, int);

void sort_words_by_occurrency(wordWithOccurrency[], size_t);