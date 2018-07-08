#include <stdlib.h>
#include <CUnit/CUnit.h>
#include "word_utils.h"
#include "test_word_utils.h"

WordWithOccurrencesPtr first;
WordWithOccurrencesPtr second;
WordWithOccurrencesPtr third;
WordWithOccurrencesPtr fourth;

size_t length = 4;
WordWithOccurrencesPtr words[4];



int init_suite_sorter(void) {
    first = create_WordWithOccurrences("first", 2);
    second = create_WordWithOccurrences("second", 5);
    third = create_WordWithOccurrences("third", 8);
    fourth = create_WordWithOccurrences("fourth", 9);
    
    words[0] = third;
    words[1] = second;
    words[2] = first;
    words[3] = fourth;


    return 0;
}

int clean_suite_sorter(void) {
    destroy_WordWithOccurrences(first);
    destroy_WordWithOccurrences(second);
    destroy_WordWithOccurrences(third);
    destroy_WordWithOccurrences(fourth);
    return 0;
}

void test_getters(void) {
    CU_ASSERT_STRING_EQUAL(get_word(first), "first");
    CU_ASSERT_EQUAL(get_occurrences(first), 2);
    CU_ASSERT_STRING_EQUAL(get_word(second), "second");
    CU_ASSERT_EQUAL(get_occurrences(second), 5);
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

    CU_ASSERT_STRING_EQUAL(get_word(words[0]), "fourth");
    CU_ASSERT_EQUAL(get_occurrences(words[0]),9);
    CU_ASSERT_STRING_EQUAL(get_word(words[1]), "third");
    CU_ASSERT_EQUAL(get_occurrences(words[1]),8);
    CU_ASSERT_STRING_EQUAL(get_word(words[2]), "second");
    CU_ASSERT_EQUAL(get_occurrences(words[2]),5);
    CU_ASSERT_STRING_EQUAL(get_word(words[3]), "first");
    CU_ASSERT_EQUAL(get_occurrences(words[3]),2);
}