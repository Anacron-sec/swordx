#include <stdlib.h>
#include <CUnit/CUnit.h>
#include "occurrency_sorter.h"

wordWithOccurrency* first;
wordWithOccurrency* second;
wordWithOccurrency* third;
wordWithOccurrency* fourth;

size_t length = 4;
wordWithOccurrency words[4];



int init_suite_occurrency_sorter(void) {
    first = create_wordWithOccurrency("first", 2);
    second = create_wordWithOccurrency("second", 5);
    third = create_wordWithOccurrency("third", 8);
    fourth = create_wordWithOccurrency("fourth", 9);
    
    words[0] = *third;
    words[1] = *second;
    words[2] = *first;
    words[3] = *fourth;


    return 0;
}

int clean_suite_occurrency_sorter(void) {
    free(first);
    free(second);
    free(third);
    free(fourth);
    return 0;
}

void test_occurency_sorting(void) {
    CU_ASSERT_STRING_EQUAL(words[0].word_chosen, "third");
    CU_ASSERT_STRING_EQUAL(words[1].word_chosen, "second");
    CU_ASSERT_STRING_EQUAL(words[2].word_chosen, "first");
    CU_ASSERT_STRING_EQUAL(words[3].word_chosen, "fourth");

    sort_words_by_occurrency(words, length);

    CU_ASSERT_STRING_EQUAL(words[0].word_chosen, "first");
    CU_ASSERT_STRING_EQUAL(words[1].word_chosen, "second");
    CU_ASSERT_STRING_EQUAL(words[2].word_chosen, "third");
    CU_ASSERT_STRING_EQUAL(words[3].word_chosen, "fourth");

}

