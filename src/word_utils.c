#include <stdlib.h>
#include "utils.h"
#include "word_utils.h"

struct WordWithOccurrences {
    char* word_chosen;
    int occurences;
};

static int compare_words_by_occurrences(const void *, const void *);

WordWithOccurrencesPtr create_WordWithOccurrences(char* word_chosen, int occurences){
    WordWithOccurrencesPtr wwo = (WordWithOccurrencesPtr) malloc(sizeof(struct WordWithOccurrences)); check_heap(wwo);
    wwo->word_chosen = word_chosen;
    wwo->occurences = occurences;

    return wwo;
}

void destroy_WordWithOccurrences(WordWithOccurrencesPtr wwoPtr) {
    free(wwoPtr);
}

void sort_words_by_occurrences (WordWithOccurrencesPtr* words, size_t length) {
    qsort(words, length, sizeof(WordWithOccurrencesPtr), compare_words_by_occurrences);
}

char* get_word(WordWithOccurrencesPtr wwoPtr) {
    return wwoPtr->word_chosen;
}
int get_occurrences(WordWithOccurrencesPtr wwoPtr) {
    return wwoPtr->occurences;
}

static int compare_words_by_occurrences(const void *first_word, const void *second_word) {
    // Qsort will implicitly pass arguments as pointers so we have to cast to a pointer and deference.
    const WordWithOccurrencesPtr* word1_ptr = first_word;
    const WordWithOccurrencesPtr* word2_ptr = second_word;

    WordWithOccurrencesPtr word1 = *word1_ptr;
    WordWithOccurrencesPtr word2 = *word2_ptr;

    return word2->occurences - word1->occurences;
}