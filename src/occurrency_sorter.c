#include <stdlib.h>
#include "utils.h"
#include "occurrency_sorter.h"

static int compare_words_by_occurrency(const void *, const void *);

wordWithOccurrency* create_wordWithOccurrency(char* word_chosen, int occurences){
    wordWithOccurrency *wwo = (wordWithOccurrency*) malloc(sizeof(wordWithOccurrency)); check_heap(wwo);
    wwo->word_chosen = word_chosen;
    wwo->occurences = occurences;

    return wwo;
}

void sort_words_by_occurrency (wordWithOccurrency words[], size_t length) {
    qsort(words, length, sizeof(wordWithOccurrency), compare_words_by_occurrency);
}

static int compare_words_by_occurrency(const void *first, const void *second) {
    wordWithOccurrency *first_word = (wordWithOccurrency *) first;
    wordWithOccurrency *second_word = (wordWithOccurrency *) second;
    
    return first_word->occurences - second_word->occurences;
}