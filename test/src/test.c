#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "test_trie.h"
#include "test_word_utils.h"

int main (void) {
    CU_pSuite pSuite_sorter = NULL;
    CU_pSuite pSuite_trie = NULL;

    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    pSuite_sorter = CU_add_suite("occurency_sorter_test_suite", init_suite_sorter, clean_suite_sorter);
    if (NULL == pSuite_sorter) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    pSuite_trie = CU_add_suite("trie_test_suite", init_suite_trie, clean_suite_trie);
    if (NULL == pSuite_trie) {
        CU_cleanup_registry();
        return CU_get_error();
    }


    if ((NULL == CU_add_test(pSuite_sorter,"sorter",test_sorting)) ||
        (NULL == CU_add_test(pSuite_sorter,"word_utils getters",test_getters)) ||
        (NULL == CU_add_test(pSuite_trie, "create_trie", test_create_trie)) ||
        (NULL == CU_add_test(pSuite_trie, "insert trie", test_insert_trie)) ||
        (NULL == CU_add_test(pSuite_trie, "get count", test_get_count)) ||
        (NULL == CU_add_test(pSuite_trie, "test sort", test_sort)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();

   CU_cleanup_registry();
   return CU_get_error();
}