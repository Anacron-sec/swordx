#include <stdlib.h>
#include "occurrency_sorter.h"

void sort_words_by_occurrency (WordWithOccurrency words[]) {
    qsort(words, sizeof(words) / sizeof(WordWithOccurrency), sizeof(words[0]), compare_words_by_occurrency);
}

static int compare_words_by_occurrency(WordWithOccurrency *first_word, WordWithOccurrency *second_word) {
    return ( first_word->occurences - second_word->occurences);
}