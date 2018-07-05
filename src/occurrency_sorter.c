#include <stdlib.h>
#include "utils.h"
#include "occurrency_sorter.h"

typedef struct wordWithOccurrency {
    char* word_chosen;
    int occurences;
} wordWithOccurrency;

static int compare_words_by_occurrency(const void *, const void *);

wordWithOccurrencyPtr create_wordWithOccurrency(char* word_chosen, int occurences){
    wordWithOccurrency *wwo = (wordWithOccurrency*) malloc(sizeof(wordWithOccurrency)); check_heap(wwo);
    wwo->word_chosen = word_chosen;
    wwo->occurences = occurences;

    return wwo;
}

void sort_words_by_occurrency (wordWithOccurrencyPtr words[], size_t length) {
    qsort(words, length, sizeof(wordWithOccurrencyPtr), compare_words_by_occurrency);
}

char* get_word(wordWithOccurrencyPtr wwoPtr) {
    return wwoPtr->word_chosen;
}
int get_occurences(wordWithOccurrencyPtr wwoPtr) {
    return wwoPtr->occurences;
}

static int compare_words_by_occurrency(const void *first, const void *second) {

    const wordWithOccurrencyPtr* first_word_ptr = first;
    const wordWithOccurrencyPtr* second_word_ptr = second;

    wordWithOccurrencyPtr first_word = *first_word_ptr;
    wordWithOccurrencyPtr second_word = *second_word_ptr;
    
    return first_word->occurences - second_word->occurences;
}