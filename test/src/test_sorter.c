#include <stdlib.h>
#include <CUnit/CUnit.h>
#include "sorter.h"
#include "test_sorter.h"

wordWithOccurrencesPtr first;
wordWithOccurrencesPtr second;
wordWithOccurrencesPtr third;
wordWithOccurrencesPtr fourth;

size_t length = 4;
wordWithOccurrencesPtr words[4];



int init_suite_sorter(void) {
    first = create_wordWithOccurrences("first", 2);
    second = create_wordWithOccurrences("second", 5);
    third = create_wordWithOccurrences("third", 8);
    fourth = create_wordWithOccurrences("fourth", 9);
    
    words[0] = third;
    words[1] = second;
    words[2] = first;
    words[3] = fourth;


    return 0;
}

int clean_suite_sorter(void) {
    free(first);
    free(second);
    free(third);
    free(fourth);
    return 0;
}

void test_sorting(void) {
    CU_ASSERT_STRING_EQUAL(get_word(words[0]), "third");
    CU_ASSERT_EQUAL(get_occurrences(words[0]),8);
    CU_ASSERT_STRING_EQUAL(get_word(words[1]), "second");
    CU_ASSERT_EQUAL(get_occurrences(words[1]),5);
    CU_ASSERT_STRING_EQUAL(get_word(words[2]), "first");
    CU_ASSERT_EQUAL(get_occurrences(words[2]),2);
    CU_ASSERT_STRING_EQUAL(get_word(words[3]), "fourth");
    CU_ASSERT_EQUAL(get_occurrences(words[3]),9);

    sort_words_by_occurrences(words, length);

    CU_ASSERT_STRING_EQUAL(get_word(words[0]), "first");
    CU_ASSERT_EQUAL(get_occurrences(words[0]),2);
    CU_ASSERT_STRING_EQUAL(get_word(words[1]), "second");
    CU_ASSERT_EQUAL(get_occurrences(words[1]),5);
    CU_ASSERT_STRING_EQUAL(get_word(words[2]), "third");
    CU_ASSERT_EQUAL(get_occurrences(words[2]),8);
    CU_ASSERT_STRING_EQUAL(get_word(words[3]), "fourth");
    CU_ASSERT_EQUAL(get_occurrences(words[3]),9);
}

