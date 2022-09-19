#include <CUnit/Basic.h>
#include "hash_table.h"

int init_suite(void) {
  // Change this function if you want to do something *before* you
  // run a test suite
  return 0;
}

void test_create_destroy()
{
   ioopm_hash_table_t *ht = ioopm_hash_table_create();
   CU_ASSERT_PTR_NOT_NULL(ht);
   ioopm_hash_table_destroy(ht);
}


void test_insert_once()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(); // allokate space for ht
  int k = 0; // make key
  char *value = "bar"; // make value

  CU_ASSERT_NOT_EQUAL(ioopm_hash_table_lookup(ht, k).value, value);// check if the key is in ht, it should not be, should be true
  ioopm_hash_table_insert(ht, k, value); // insert key and value in ht
  CU_ASSERT_EQUAL(ioopm_hash_table_lookup(ht, k).value, value); // check if in ht, should be true

  ioopm_hash_table_destroy(ht);
}

void test_size()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int k = 0; // make key
  char *value = "bar";
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);
  ioopm_hash_table_insert(ht, k, value);
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 1);

  ioopm_hash_table_destroy(ht);
  
}

/*
void test_values()
{

bool found[5] = {false};
char *values[5] = {"three", "ten", "fortytwo", "zero", "ninetynine"};
ioopm_hash_table_t *ht = ioopm_hash_table_create();

ioopm_hash_table_insert(ht, 3, "three");
ioopm_hash_table_insert(ht, 10,"ten");
ioopm_hash_table_insert(ht, 42,"fortytwo");
ioopm_hash_table_insert(ht, 0,"zero");
ioopm_hash_table_insert(ht, 99,"ninetynine");
char *found_values[5] = {"three", "ten", "fortytwo", "zero", "ninetynine"}; //ioopm_hash_table_values(ht);
for(int i = 0; i < 5; i++)
  {
    for(int k = 0; k < 5; k++)
    {
      if(found_values[i] == values[k])
      {
        found[k] = true;
        k = 4;
      }
      else if(k==4)
      {
        CU_FAIL("Found a value that was never inserted!");
      }
    }
  }

 for (int z = 0; z<5; z++)
  {
    CU_ASSERT_TRUE(found[z]);
  }

ioopm_hash_table_destroy(ht);
}


void test_keys()
{
  int keys[5] = {3, 10, 42, 0, 99};
  bool found[5] = {false};
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_insert(ht, 3, "three");
  ioopm_hash_table_insert(ht, 10,"ten");
  ioopm_hash_table_insert(ht, 42,"fortytwo");
  ioopm_hash_table_insert(ht, 0,"zero");
  ioopm_hash_table_insert(ht, 99,"ninetynine");
  int *arr_key = ioopm_hash_table_keys(ht);

  for(int i = 0; i < 5; i++)
  {
    for(int k = 0; k < 5; k++)
    {
      if(arr_key[i] == keys[k])
      {
        found[k] = true;
        k = 4;
      }
      else if(k==4)
      {
        CU_FAIL("Found a key that was never inserted!");
      }
    }
  }

  for (int z = 0; z<5; z++)
  {
    CU_ASSERT_TRUE(found[z]);
  }
  ioopm_hash_table_destroy(ht);
}

void test_symmetrical()
{
  int keys[5] = {3, 10, 42, 0, 99};
  char *values[5] = {"three", "ten", "fortytwo", "zero", "ninetynine"};

  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  for(int i = 0; i < 5; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }

  int arr_key[5] = {3, 10, 42, 0, 99}; // ioopm_hash_table_keys(ht);
  char *arr_val[5] = {"three", "ten", "fortytwo", "zero", "ninetynine"}; // ioopm_hash_table_values(ht);

  for(int j = 0; j < 5; j++)
  {
    if((arr_key[j] == keys[j]) && (arr_val[j] == values[j]))
    {
      j = 4;
    }
    else if(j==4)
    {
      CU_FAIL("Found a ...that was never inserted!")
    }
    
  }

ioopm_hash_table_destroy(ht);
}
*/

void test_has_key()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_insert(ht, -1, "foo");
  ioopm_hash_table_insert(ht, 0, "bar");
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht,0));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht,-1));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht,13));

  ioopm_hash_table_destroy(ht);
}


void test_lookup_empty()
{
  
   ioopm_hash_table_t *ht = ioopm_hash_table_create();
   for (int i = 0; i < 18; ++i) /// 18 is a bit magical
     {
       CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, i).value);
     }
   CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, -1).value);
   ioopm_hash_table_destroy(ht);
}

void test_remove()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(); // skapa hash table
  int k = 0; // make key
  char *value = "bar";

  ioopm_hash_table_insert(ht, k, value); // instert i ht
  CU_ASSERT_EQUAL(ioopm_hash_table_lookup(ht, k).value, "bar"); // check that it inserted correct
  ioopm_hash_table_remove(ht, k); // remove key
  CU_ASSERT_NOT_EQUAL(ioopm_hash_table_lookup(ht, k).value, value); //check that is got removed

  ioopm_hash_table_destroy(ht);
}


int clean_suite(void) {
  // Change this function if you want to do something *after* you
  // run a test suite
  return 0;
}

// These are example test functions. You should replace them with
// functions of your own.
void test1(void) {
  CU_ASSERT(42);
}

void test2(void) {
  CU_ASSERT_EQUAL(1 + 1, 2);
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
    //(CU_add_test(my_test_suite, "test_lookup_miss", test_lookup_miss) == NULL) ||
    (CU_add_test(my_test_suite, "test_create_destroy", test_create_destroy) == NULL) ||
    (CU_add_test(my_test_suite, "test_insert_once", test_insert_once) == NULL) ||
    (CU_add_test(my_test_suite, "test_lookup_empty", test_lookup_empty) == NULL) ||
    (CU_add_test(my_test_suite, "test_lookup_empty", test_remove) == NULL) ||
    (CU_add_test(my_test_suite, "test_lookup_empty", test_size) == NULL) ||
    //(CU_add_test(my_test_suite, "test_lookup_empty", test_symmetrical) == NULL) ||
    //(CU_add_test(my_test_suite, "test_lookup_empty", test_keys) == NULL) ||
    //(CU_add_test(my_test_suite, "test_lookup_empty", test_values) == NULL) ||
    (CU_add_test(my_test_suite, "test_lookup_empty", test_has_key) == NULL) ||
    0
  )
    {
      // If adding any of the tests fails, we tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
    }

  // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
  // Use CU_BRM_NORMAL to only print errors and a summary
  CU_basic_set_mode(CU_BRM_NORMAL);

  // This is where the tests are actually run!
  CU_basic_run_tests();

  // Tear down CUnit before exiting
  CU_cleanup_registry();
  return CU_get_error();
}
