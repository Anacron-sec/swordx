#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "test_trie.h"
#include "test_trie_counted.h"
#include "test_sorter.h"

int main (void) {
    CU_pSuite pSuite_trie = NULL;
    CU_pSuite pSuite_trie_c = NULL;
    CU_pSuite pSuite_sorter = NULL;

    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    pSuite_trie = CU_add_suite("trie_test_suite", init_suite_trie, clean_suite_trie);
    if (NULL == pSuite_trie) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    pSuite_trie_c = CU_add_suite("trie_c_test_suite", init_suite_trie_c, clean_suite_trie_c);
    if (NULL == pSuite_trie_c) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    
    pSuite_sorter = CU_add_suite("occurency_sorter_test_suite", init_suite_sorter, clean_suite_sorter);
    if (NULL == pSuite_sorter) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite_trie, "create_trie", test_create_trie)) ||
        (NULL == CU_add_test(pSuite_trie, "insert_trie with various cases", test_insert_word)) ||
        (NULL == CU_add_test(pSuite_trie, "process function", test_process_function)) ||
        (NULL == CU_add_test(pSuite_trie_c, "create_trie counted", test_create_trie_c)) ||
        (NULL == CU_add_test(pSuite_trie_c, "trie_c insert new word", test_insert_new_word)) ||
        (NULL == CU_add_test(pSuite_trie_c,"trie_c insert_dup_word",test_insert_dup_word)) ||
        (NULL == CU_add_test(pSuite_sorter,"sorter",test_sorting)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();

   CU_cleanup_registry();
   return CU_get_error();
}