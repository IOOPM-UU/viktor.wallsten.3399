#include "iterator.h"
#include <CUnit/Basic.h>

int init_suite(void) {
  // Change this function if you want to do something *before* you
  // run a test suite
  return 0;
}

int clean_suite(void) {
  // Change this function if you want to do something *after* you
  // run a test suite
  return 0;
}

void test_iter_create_destroy()
{
    ioopm_list_t *list = ioopm_linked_list_create(compare_int);
    ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
    CU_ASSERT_PTR_NOT_NULL(iter);
    ioopm_iterator_destroy(iter);
    ioopm_linked_list_destroy(list);

}
void test_iter_has_next()
{
    ioopm_list_t *list = ioopm_linked_list_create(compare_int);
    
    ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
    CU_ASSERT_FALSE(ioopm_iterator_has_next(iter));
    ioopm_iterator_destroy(iter);
    
    ioopm_linked_list_insert(list, 0, int_elem(10));
    iter = ioopm_list_iterator(list);
    CU_ASSERT_FALSE(ioopm_iterator_has_next(iter));
    ioopm_iterator_destroy(iter);
    
    ioopm_linked_list_insert(list, 1, int_elem(4));
    iter = ioopm_list_iterator(list);
    CU_ASSERT_TRUE(ioopm_iterator_has_next(iter));
    
    ioopm_iterator_destroy(iter);
    ioopm_linked_list_destroy(list);
}

void test_iter_next()
{
    ioopm_list_t *list = ioopm_linked_list_create(compare_int);
    elem_t val = ptr_elem(NULL);
    
    ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
    ioopm_iterator_next(iter, &val);
    CU_ASSERT_EQUAL(val.i, 0);
    ioopm_iterator_destroy(iter);
    
    ioopm_linked_list_insert(list, 0, int_elem(10));
    
    
    iter = ioopm_list_iterator(list);
    ioopm_iterator_next(iter, &val);
    CU_ASSERT_EQUAL(val.i, 0);
    ioopm_iterator_destroy(iter);
    
    
    ioopm_linked_list_insert(list, 1, int_elem(4));
    
    
    iter = ioopm_list_iterator(list);
    ioopm_iterator_next(iter, &val);
    CU_ASSERT_EQUAL(val.i, 4);
    ioopm_iterator_next(iter, &val);
    CU_ASSERT_EQUAL(val.i, 0);
    
    ioopm_iterator_destroy(iter);
    ioopm_linked_list_destroy(list);
}


void test_iter_current_and_reset()
{
    ioopm_list_t *list = ioopm_linked_list_create(compare_int);

    ioopm_linked_list_append(list, int_elem(1));
    
    ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
    CU_ASSERT(ioopm_iterator_current(iter).i);
    ioopm_iterator_destroy(iter);
    
    ioopm_linked_list_insert(list, 0, int_elem(10));
    
    iter = ioopm_list_iterator(list);
    CU_ASSERT_EQUAL(ioopm_iterator_current(iter).i, 10);
    ioopm_iterator_destroy(iter);
    
    
    ioopm_linked_list_insert(list, 1, int_elem(4));
    
    
    iter = ioopm_list_iterator(list);
    
    elem_t a = ptr_elem(NULL);
    ioopm_iterator_next(iter, &a);
    CU_ASSERT_EQUAL(a.i,4);
    
    CU_ASSERT_EQUAL(ioopm_iterator_current(iter).i, 4);
    
    CU_ASSERT_NOT_EQUAL(ioopm_iterator_current(iter).i, 10);
    
    ioopm_iterator_reset(iter);
    
    CU_ASSERT_EQUAL(ioopm_iterator_current(iter).i, 10);
    
    
    ioopm_iterator_destroy(iter);
    ioopm_linked_list_destroy(list);
}


int main() {
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite my_test_suite = CU_add_suite("My awesome test suite", init_suite, clean_suite);
  if (my_test_suite == NULL) {
      // If the test suite could not be added, tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
  }

  // This is where we add the test functions to our test suite.
  // For each call to CU_add_test we specify the test suite, the
  // name or description of the test, and the function that runs
  // the test in question. If you want to add another test, just
  // copy a line below and change the information
  if (
    (CU_add_test(my_test_suite, "A iter test\n", test_iter_create_destroy) == NULL) ||
      (CU_add_test(my_test_suite, "A iter has next test\n", test_iter_has_next) == NULL) ||
      (CU_add_test(my_test_suite, "A iter next test\n", test_iter_next) == NULL) ||
      (CU_add_test(my_test_suite, "A iter current test\n", test_iter_current_and_reset) == NULL) ||
    0
  )
    {
      // If adding any of the tests fails, we tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
    }

  // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
  // Use CU_BRM_NORMAL to only print errors and a summary
  CU_basic_set_mode(CU_BRM_VERBOSE);

  // This is where the tests are actually run!
  CU_basic_run_tests();

  // Tear down CUnit before exiting
  CU_cleanup_registry();
  return CU_get_error();
}
