#include "linked_list.h"
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

void test_linked_list_create_destroy()
{
  ioopm_list_t *list = ioopm_linked_list_create();
   CU_ASSERT_PTR_NOT_NULL(list);
   ioopm_linked_list_destroy(list);

}

void test_insert()
{
    ioopm_list_t *list = ioopm_linked_list_create();
    ioopm_linked_list_insert(list, 0, 5);
    ioopm_linked_list_insert(list,1, 8);
    ioopm_linked_list_insert(list,2, 56);
    ioopm_linked_list_insert(list,1, 98);
    ioopm_linked_list_insert(list,4, 69);
    ioopm_linked_list_insert(list,-1, 48);
    
    int a = ioopm_linked_list_get(list,-1);
    int b = ioopm_linked_list_get(list, 0);
    int c = ioopm_linked_list_get(list, 4);
    int d = ioopm_linked_list_get(list, 1);
    int e = ioopm_linked_list_get(list, 2);


    CU_ASSERT_PTR_NULL(a);
    CU_ASSERT_EQUAL(b, 5);
    CU_ASSERT_EQUAL(c, 69);
    CU_ASSERT_EQUAL(d, 98);
    CU_ASSERT_EQUAL(e, 8);

    ioopm_linked_list_destroy(list);

}

void test_prepend()
{
    ioopm_list_t *list = ioopm_linked_list_create();
    ioopm_linked_list_prepend(list, 5);
    ioopm_linked_list_prepend(list, 8);
    CU_ASSERT_EQUAL(ioopm_linked_list_remove(list, 0), 8);
    CU_ASSERT_EQUAL(ioopm_linked_list_remove(list, 0), 5);
    ioopm_linked_list_destroy(list);
}

void test_link_remove()
{
    ioopm_list_t *list = ioopm_linked_list_create();
    ioopm_linked_list_insert(list, 0, 5);
    ioopm_linked_list_insert(list, 1, 6);
    ioopm_linked_list_insert(list, 2, 7);
    ioopm_linked_list_insert(list, 3, 9);


    //ioopm_linked_list_insert(list, -1, 9);
    CU_ASSERT_EQUAL(ioopm_linked_list_remove(list, 0), 5);
    CU_ASSERT_EQUAL(ioopm_linked_list_remove(list, 2), 9);
    CU_ASSERT_EQUAL(ioopm_linked_list_remove(list, 1), 7);
    CU_ASSERT_EQUAL(ioopm_linked_list_remove(list, 0), 6);
    
    //CU_ASSERT_NOT_EQUAL(ioopm_linked_list_remove(list, -1), 9);

    free(list);    
}

void test_lookup()
{
    ioopm_list_t *list = ioopm_linked_list_create();
    CU_ASSERT_FALSE(ioopm_linked_list_contains(list, 6));

    ioopm_linked_list_insert(list, 0, 5);
    ioopm_linked_list_insert(list, 1, 78);
    ioopm_linked_list_insert(list, 2, 75);

    CU_ASSERT_TRUE(ioopm_linked_list_contains(list, 78));
    CU_ASSERT_TRUE(ioopm_linked_list_contains(list, 5));
    CU_ASSERT_TRUE(ioopm_linked_list_contains(list, 75));


    ioopm_linked_list_destroy(list);
}

void test_size()
{
    ioopm_list_t *list = ioopm_linked_list_create();
    CU_ASSERT_EQUAL(ioopm_linked_list_size(list), 0);
    ioopm_linked_list_insert(list, 0, 78);
    ioopm_linked_list_insert(list, 1, 7);

    CU_ASSERT_NOT_EQUAL(ioopm_linked_list_size(list), 0);
    CU_ASSERT_EQUAL(ioopm_linked_list_size(list), 2);

    ioopm_linked_list_destroy(list);
}

void test_empty()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  CU_ASSERT_TRUE(ioopm_linked_list_is_empty(list));
  ioopm_linked_list_insert(list, 0, 7);
  CU_ASSERT_FALSE(ioopm_linked_list_is_empty(list));

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
    (CU_add_test(my_test_suite, "A insert test\n", test_insert) == NULL) ||
    (CU_add_test(my_test_suite, "A destroy test\n", test_linked_list_create_destroy) == NULL) ||
    (CU_add_test(my_test_suite, "A remove test\n", test_link_remove) == NULL) ||
    (CU_add_test(my_test_suite, "A prepend test\n", test_prepend) == NULL) ||
    (CU_add_test(my_test_suite, "A lookup test\n", test_lookup) == NULL) ||
    (CU_add_test(my_test_suite, "A size test\n", test_size) == NULL) ||
    (CU_add_test(my_test_suite, "A empty test\n", test_empty) == NULL) ||
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