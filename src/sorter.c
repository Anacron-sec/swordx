#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "sorter.h"

struct wordWithOccurrences {
    char* word_chosen;
    int occurences;
};

static int compare_words_by_occurrences(const void *, const void *);

wordWithOccurrencesPtr create_wordWithOccurrences(char* word_chosen, int occurences){
    wordWithOccurrencesPtr wwo = (wordWithOccurrencesPtr) malloc(sizeof(struct wordWithOccurrences)); check_heap(wwo);
    wwo->word_chosen = word_chosen;
    wwo->occurences = occurences;

    return wwo;
}

void destroy_wordWithOccurrences(wordWithOccurrencesPtr wwoPtr) {
    free(wwoPtr);
}

void sort_words_by_occurrences (wordWithOccurrencesPtr* words, size_t length) {
    qsort(words, length, sizeof(wordWithOccurrencesPtr), compare_words_by_occurrences);
}

char* get_word(wordWithOccurrencesPtr wwoPtr) {
    return wwoPtr->word_chosen;
}
int get_occurrences(wordWithOccurrencesPtr wwoPtr) {
    return wwoPtr->occurences;
}

static int compare_words_by_occurrences(const void *first_word, const void *second_word) {
    // Qsort will implicitly pass arguments as pointers so we have to cast to a pointer and deference.
    const wordWithOccurrencesPtr* word1_ptr = first_word;
    const wordWithOccurrencesPtr* word2_ptr = second_word;

    wordWithOccurrencesPtr word1 = *word1_ptr;
    wordWithOccurrencesPtr word2 = *word2_ptr;

    return word1->occurences - word2->occurences;
}