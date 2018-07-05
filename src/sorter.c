#include <stdlib.h>
#include "utils.h"
#include "sorter.h"

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
int get_occurrences(wordWithOccurrencyPtr wwoPtr) {
    return wwoPtr->occurences;
}

static int compare_words_by_occurrency(const void *first_word, const void *second_word) {
    // Qsort will implicitly pass arguments as pointers so we have to convert to a pointer and deference
    return (*((const wordWithOccurrencyPtr*)first_word))->occurences - (*((const wordWithOccurrencyPtr*)second_word))->occurences;
}