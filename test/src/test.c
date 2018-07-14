#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "test_trie.h"
#include "test_word_utils.h"

int main (void) {
    CU_pSuite pSuite_word_utils = NULL;
    CU_pSuite pSuite_trie = NULL;

    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    pSuite_word_utils = CU_add_suite("occurency_word_utils_test_suite", init_suite_word_utils, clean_suite_word_utils);
    if (NULL == pSuite_word_utils) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    pSuite_trie = CU_add_suite("trie_test_suite", init_suite_trie, clean_suite_trie);
    if (NULL == pSuite_trie) {
        CU_cleanup_registry();
        return CU_get_error();
    }


    if ((NULL == CU_add_test(pSuite_word_utils,"word_utils getters",test_getters)) ||
        (NULL == CU_add_test(pSuite_word_utils,"word_utils sorter",test_sorting)) ||
        (NULL == CU_add_test(pSuite_trie, "create_trie", test_create_trie)) ||
        (NULL == CU_add_test(pSuite_trie, "insert trie", test_insert_trie)) ||
        (NULL == CU_add_test(pSuite_trie, "get count", test_get_count)) ||
        (NULL == CU_add_test(pSuite_trie,"write to file",test_write_trie)))
        //(NULL == CU_add_test(pSuite_trie, "test sort", test_sort)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();

   CU_cleanup_registry();
   return CU_get_error();
}