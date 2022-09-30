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
  ioopm_list_t *list = ioopm_linked_list_create(NULL);
   CU_ASSERT_PTR_NOT_NULL(list);
   ioopm_linked_list_destroy(list);

}

void test_insert()
{
    ioopm_list_t *list = ioopm_linked_list_create(compare_int);
    ioopm_linked_list_insert(list, 0, int_elem(5));
    ioopm_linked_list_insert(list,1, int_elem(8));
    ioopm_linked_list_insert(list,2, int_elem(56));
    ioopm_linked_list_insert(list,1, int_elem(98));
    ioopm_linked_list_insert(list,4, int_elem(69));
    ioopm_linked_list_insert(list,-1, int_elem(48));
    
    CU_ASSERT_FALSE(ioopm_linked_list_contains(list, int_elem(48)));
    CU_ASSERT_TRUE(ioopm_linked_list_contains(list, int_elem(56)));
    CU_ASSERT_TRUE(ioopm_linked_list_contains(list, int_elem(98)));
    CU_ASSERT_TRUE(ioopm_linked_list_contains(list, int_elem(5)));
    CU_ASSERT_TRUE(ioopm_linked_list_contains(list, int_elem(69)));

    ioopm_linked_list_destroy(list);

}

void test_prepend()
{
    ioopm_list_t *list = ioopm_linked_list_create(NULL);
    ioopm_linked_list_prepend(list, int_elem(5));
    CU_ASSERT_EQUAL(1, ioopm_linked_list_size(list));
    ioopm_linked_list_prepend(list, int_elem(8));
    CU_ASSERT_EQUAL(2, ioopm_linked_list_size(list));
    ioopm_linked_list_destroy(list);
}

void test_link_remove()
{
    ioopm_list_t *list = ioopm_linked_list_create(NULL);
    ioopm_linked_list_insert(list, 0, int_elem(5));
    ioopm_linked_list_insert(list, 1, int_elem(6));
    ioopm_linked_list_insert(list, 2, int_elem(7));
    ioopm_linked_list_insert(list, 3, int_elem(9));

    
    ioopm_linked_list_remove(list, 0);
    ioopm_linked_list_remove(list, 2);
    ioopm_linked_list_remove(list, 1);
    ioopm_linked_list_remove(list, 0);
    
    CU_ASSERT_TRUE(ioopm_linked_list_is_empty(list));
  
    free(list);    
}

void test_lookup()
{
    ioopm_list_t *list = ioopm_linked_list_create(compare_int);
    CU_ASSERT_FALSE(ioopm_linked_list_contains(list, int_elem(6)));

    ioopm_linked_list_insert(list, 0, int_elem(5));
    ioopm_linked_list_insert(list, 1, int_elem(78));
    ioopm_linked_list_insert(list, 2, int_elem(75));

    CU_ASSERT_TRUE(ioopm_linked_list_contains(list, int_elem(78)));
    CU_ASSERT_TRUE(ioopm_linked_list_contains(list, int_elem(5)));
    CU_ASSERT_TRUE(ioopm_linked_list_contains(list, int_elem(75)));


    ioopm_linked_list_destroy(list);
}

void test_size()
{
    ioopm_list_t *list = ioopm_linked_list_create(NULL);
    CU_ASSERT_EQUAL(ioopm_linked_list_size(list), 0);
    ioopm_linked_list_insert(list, 0, int_elem(78));
    ioopm_linked_list_insert(list, 1, int_elem(7));

    CU_ASSERT_NOT_EQUAL(ioopm_linked_list_size(list), 0);
    CU_ASSERT_EQUAL(ioopm_linked_list_size(list), 2);

    ioopm_linked_list_destroy(list);
}

void test_empty()
{
  ioopm_list_t *list = ioopm_linked_list_create(NULL);
  CU_ASSERT_TRUE(ioopm_linked_list_is_empty(list));
  ioopm_linked_list_insert(list, 0, int_elem(7));
  CU_ASSERT_FALSE(ioopm_linked_list_is_empty(list));

  ioopm_linked_list_destroy(list);
}

void apply_to_all_test()
{
  ioopm_list_t *list = ioopm_linked_list_create(compare_int);
  elem_t key = ptr_elem("hejsan");
  elem_t value = int_elem(2);

  for (int i = 0; i < 5; i++)
  {
    ioopm_linked_list_insert(list, i, value);
  }
  
  int *new = 3;

  ioopm_linked_list_apply_to_all(list, change_elem, &new);

  CU_ASSERT_TRUE(ioopm_linked_list_contains(list, int_elem(3)));

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
    (CU_add_test(my_test_suite, "A apply to all\n", apply_to_all_test) == NULL) ||
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