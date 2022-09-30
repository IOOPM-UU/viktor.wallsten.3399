#include "hash_table.h"
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


void test_create_destroy()
{
   ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL, NULL);
   CU_ASSERT_PTR_NOT_NULL(ht);
   ioopm_hash_table_destroy(ht);
}

void test_insert_once()
{
  
    ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_str, hash_func);              
    elem_t k = int_elem(0);                                                               
    elem_t v = ptr_elem("bar");                                                 
    
    CU_ASSERT(!(ioopm_hash_table_lookup(ht, k, &v)));              
    ioopm_hash_table_insert(ht, k, v);                                  
    CU_ASSERT(ioopm_hash_table_lookup(ht, k, &v));   

    ioopm_hash_table_insert(ht, k, ptr_elem("ny bar")); // sätter in ett nytt value

    elem_t expected_val = ptr_elem("ny bar");
    ioopm_hash_table_lookup(ht, k, &v);
    CU_ASSERT(compare_str(v, expected_val));

    elem_t key = int_elem(-1);
    elem_t expected2 = ptr_elem("foo");
    ioopm_hash_table_insert(ht, key, expected2); // negative val
    ioopm_hash_table_lookup(ht, key, &v);

    CU_ASSERT(compare_str(v, expected2));

    
    ioopm_hash_table_destroy(ht);                                          
}


void test_insert_existing_key()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_str, hash_func);                     
    elem_t k = int_elem(0);                                                               
    elem_t v1 = ptr_elem("foo");                                                  
    elem_t v2 = ptr_elem("bar");
    elem_t expected = ptr_elem("bar");
  
    ioopm_hash_table_insert(ht, k, v1);                                  
    ioopm_hash_table_insert(ht, k, v2);                                    
    CU_ASSERT(compare_str(expected, v2));                  
    
    ioopm_hash_table_destroy(ht);                                           
}

void test_insert_and_lookup_negative_key()
{
  
    ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_str, hash_func);                     
    elem_t k = int_elem(-1);                                                               
    elem_t v = ptr_elem("bar");
    elem_t expected = ptr_elem("bar");                                                  

    CU_ASSERT(!ioopm_hash_table_lookup(ht, k, &v));              
    ioopm_hash_table_insert(ht, k, v);                                  
    CU_ASSERT(compare_str(expected, v));                  
    ioopm_hash_table_destroy(ht);     
}

void test_lookup_empty()
{
   ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL, hash_func);
   elem_t v = ptr_elem(NULL);
   elem_t key = int_elem(-1);
   for (int i = 0; i < No_buckets + 1; ++i) /// 18 is a bit magical
     {
       CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, int_elem(i), &v));
     }
   CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, key, &v));
   ioopm_hash_table_destroy(ht);
}


void test_remove_key()
{
  
    ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_int, hash_func);                     
    char bar = 'b';
    elem_t k = ptr_elem("hejsan");                                                               
    elem_t v = int_elem(bar);
    elem_t result = ptr_elem(NULL);                                                  

    ioopm_hash_table_insert(ht, k, v);                                  
    CU_ASSERT(ioopm_hash_table_lookup(ht, k, &result));     
    CU_ASSERT(compare_int(result, v));             
    ioopm_hash_table_remove(ht, k, &result);
    CU_ASSERT(!ioopm_hash_table_lookup(ht, k, &result));
    ioopm_hash_table_destroy(ht);     
}


void test_remove_empty()
{
   elem_t v = ptr_elem(NULL);
   ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL, hash_func);
   for (int i = 0; i < No_buckets + 1; ++i) 
     {
       CU_ASSERT_PTR_NULL(ioopm_hash_table_remove(ht, int_elem(i), &v));
     }
   CU_ASSERT_PTR_NULL(ioopm_hash_table_remove(ht, int_elem(-1), &v));
   ioopm_hash_table_destroy(ht);
}


//To get going, let us start with something easy: counting the number of entries in a hash table. 
//As always, start by making a test that takes the size of an empty hash table, a hash table with one entry,
// and a hash table with several entries. This could be written as a single test with multiple asserts, or as multiple shorter tests.

//int ioopm_hash_table_size(ioopm_hash_table_t *ht);


void test_table_size()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL, hash_func);
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);
  elem_t k = int_elem(0);                                                          
  elem_t v = ptr_elem("bar");                                                  
  ioopm_hash_table_insert(ht, k, v);
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 1);
  for (int i = 0; i < No_buckets; ++i)
     {
       ioopm_hash_table_insert(ht, int_elem(i), v);
     }
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), No_buckets);
  ioopm_hash_table_destroy(ht);

}

void test_is_table_empty()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL, hash_func);
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  elem_t k = int_elem(0);                                                          
  elem_t v = ptr_elem("bar");                                                  
  ioopm_hash_table_insert(ht, k, v);
  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_destroy(ht);

}

void test_table_clear() // något är lurt.... next blir null när den inte borde. hmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
{ 
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL, hash_func);
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  elem_t result = ptr_elem(NULL);
  for (int i = 0; i < 72; ++i)
  {
    ioopm_hash_table_insert(ht, int_elem(i), ptr_elem("bar"));
  }
  ioopm_hash_table_insert(ht, int_elem(72), ptr_elem("foo"));
  ioopm_hash_table_lookup(ht, int_elem(72), &result);
  CU_ASSERT_EQUAL(result.c, "foo");
  printf("ht size %ld\n", ioopm_hash_table_size(ht));
  ioopm_hash_table_clear(ht);
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  free(ht);

}

void test_get_keys()
{

  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL, hash_func);
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));

  int keys[5] = {3, 10, 42, 0, 99};

  bool found[5] = {false};

  
  for (int i = 0; i < 5; i++)
  {
    ioopm_hash_table_insert(ht, int_elem(keys[i]), ptr_elem("bar"));
    CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));
    
  }

ioopm_list_t *found_keys = ioopm_hash_table_keys(ht);
link_t *current = found_keys->first;
int index = 0;
while(current != NULL)
  {
   
   printf("found keys idex %d = %d\n", index, current->element.i);
   current = current->next;
   index++;
    
  }

current = found_keys->first;

while(current != NULL)
  {
    for (int j = 0; j < 5; ++j)
    {
      if (current->element.i == keys[j])
      {
        found[j] = true;
        current = current->next;
      }
    }
  }
  
  for (int i = 0; i < 5; ++i)
  {
    CU_ASSERT_TRUE(found[i]);
  }

  ioopm_linked_list_destroy(found_keys);
  ioopm_hash_table_destroy(ht);
}


void test_get_values()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_str, hash_func);
  ioopm_hash_table_insert(ht, int_elem(7), ptr_elem("sju"));
  ioopm_hash_table_insert(ht, int_elem(15), ptr_elem("femton"));
  ioopm_list_t *values = ioopm_hash_table_values(ht);

  elem_t value1 = ioopm_linked_list_get(values, 0);
  elem_t value2 = ioopm_linked_list_get(values, 1);

  CU_ASSERT(compare_str(ptr_elem("sju"), value1));
  CU_ASSERT(compare_str(ptr_elem("femton"), value2));

  ioopm_linked_list_destroy(values);
  ioopm_hash_table_destroy(ht);

}


void test_check_value_and_keys_match()
{
int keys[5] = {3, 10, 42, 0, 99};


//2. Create another array values of N strings (e.g. char *values[5] = {"three", "ten", "fortytwo", "zero", "ninetynine"}).
char *values[5] = {"three", "ten", "fortytwo", "zero", "ninetynine"};

//3. Insert all the keys from keys into a fresh hash table with values from the corresponding indices in values.
ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_str, hash_func);
for (int i = 0; i < 5; ++i)
  {
    ioopm_hash_table_insert(ht, int_elem(keys[i]), ptr_elem(values[i]));
  }

//4. Call ioopm_hash_table_keys() and ioopm_hash_table_values() on the hash table and iterate over the two resulting arrays.
  //  4.1. For each key k and value v at the same index i, find the corresponding index j of k in keys and assert that v is equal to values[j].
  //  4.2. If you find a key (or value) that is not among the original keys (or values), you can register a failed assertion by calling CU_FAIL("Found a ... that was never inserted!")

  ioopm_list_t *found_keys = ioopm_hash_table_keys(ht);
  //int found_keys[5] = {10, 42, 0, 99, 3};
  link_t *current = found_keys->first;



 ioopm_list_t *found_values = ioopm_hash_table_values(ht);
  //char *found_values[5] = {"ten", "fortytwo", "zero", "ninetynine", "three"};


while(current != NULL)
{
  for (int i = 0; i < 5; ++i)
  {
    for (int j = 0; j < 5; ++j)
  {
    if(current->element.i == keys[j])
    {
      CU_ASSERT_EQUAL(ioopm_linked_list_get(found_values, i).c, values[j]);
      current = current->next;
      j = 4;
    }
    else if (j==4)
    {
      CU_FAIL("Found a key that was never inserted!");
    }
  }
  }
}

  ioopm_linked_list_destroy(found_keys);
  ioopm_linked_list_destroy(found_values);
  //free(found_values);
  ioopm_hash_table_destroy(ht);
}


void test_has_key()
{
  
    ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL, hash_func);              //create a new hashtable
    elem_t k = int_elem(0);                                                               //the key k
    elem_t v = ptr_elem("bar");                                                  //the value v
    CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, k));  
    ioopm_hash_table_insert(ht, k, v);                                  //insert the key k with the value value
    CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, k));                  //check that the key is in the table
    ioopm_hash_table_destroy(ht);
    
}

void test_has_value()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL, hash_func);              //create a new hashtable
    elem_t k = int_elem(0);                                                               //the key k
    elem_t v = ptr_elem("bar");                                                  //the value v
    CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, v));
    ioopm_hash_table_insert(ht, k, v);                                
    CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, v));                 
                                                                      
    ioopm_hash_table_destroy(ht);                                           
}


void test_change_all_values()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL, hash_func);  
    for (int i = 0; i < 5; ++i)
    {
      ioopm_hash_table_insert(ht, int_elem(i), ptr_elem("bar"));
    }

    //char *test_value = calloc(1, sizeof("bar"));
   // *test_value = "bar";
    
    CU_ASSERT_TRUE(ioopm_hash_table_all_value(ht, ptr_elem("bar")));
    CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, ptr_elem("bar")));



    CU_ASSERT_FALSE(ioopm_hash_table_all_value(ht, ptr_elem("ba")));
    CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, ptr_elem("ba")));

    //int *test_key = calloc(1, sizeof(int[1]));
    //test_key[0] = 10;
   
    //CU_ASSERT_FALSE(ioopm_hash_table_all(ht, key_equiv, test_key));

    CU_ASSERT_TRUE(ioopm_hash_table_all_key_smaller(ht, int_elem(10)));
    CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, int_elem(2)));



    CU_ASSERT_FALSE(ioopm_hash_table_all_value(ht, ptr_elem("ba")));
    CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, ptr_elem("ba")));
    
    char *v= "hej";
    
    ioopm_hash_table_apply_to_all(ht, change_values_str, &v);

    elem_t value = ptr_elem(NULL);
    for (int i = 0; i < No_buckets; ++i)
    {
      ioopm_hash_table_lookup(ht, int_elem(i), &value);
      printf("key %d, value = %s\n", i, value.c);
    }

    
    CU_ASSERT_TRUE(ioopm_hash_table_all_value(ht, ptr_elem(v)));
    CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, ptr_elem(v)));


    CU_ASSERT_FALSE(ioopm_hash_table_all_value(ht, ptr_elem("bar")));
    CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, ptr_elem("bar")));


/*
    char *v_copy = strdup(v);

    CU_ASSERT_TRUE(ioopm_hash_table_all_value(ht, v_copy));
    CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, v_copy));




    int *test_key = calloc(1, sizeof(int[1]));
    test_key[0] = 10;
   
    CU_ASSERT_FALSE(ioopm_hash_table_all(ht, key_equiv, test_key));
     
    char *v= "hej";
    
   
    
    CU_ASSERT_TRUE(ioopm_hash_table_all(ht, value_equiv, *v));
    
    
    CU_ASSERT_TRUE(ioopm_hash_table_all(ht, value_equiv, v_copy));
    free(test_key);
    free(v_copy);
*/
    ioopm_hash_table_destroy(ht);                                           //clear the memory used by the table
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
    (CU_add_test(my_test_suite, "A destroy test\n", test_create_destroy) == NULL) ||
    (CU_add_test(my_test_suite, "a inserting key test\n", test_insert_once) == NULL) ||
    (CU_add_test(my_test_suite, "inserting & lookup negative key test\n", test_insert_and_lookup_negative_key) == NULL) ||
    (CU_add_test(my_test_suite, "a inserting a existing key test\n", test_insert_existing_key) == NULL) ||
    (CU_add_test(my_test_suite, "looking up keys in an empty table test\n", test_lookup_empty) == NULL) ||
    (CU_add_test(my_test_suite, "remove value by key test\n", test_remove_key) == NULL) ||
    (CU_add_test(my_test_suite, "remove keys in an empty table test\n", test_remove_empty) == NULL) ||
    (CU_add_test(my_test_suite, "counts keys in table test\n", test_table_size) == NULL) ||
    (CU_add_test(my_test_suite, "is the table empty test\n", test_is_table_empty) == NULL) ||
    (CU_add_test(my_test_suite, " table clearing test\n", test_table_clear) == NULL) ||
    (CU_add_test(my_test_suite, " getting all keys test\n", test_get_keys) == NULL) ||
    (CU_add_test(my_test_suite, " getting all values test\n", test_get_values) == NULL) ||
    (CU_add_test(my_test_suite, " matching all gotten keys and values test\n", test_check_value_and_keys_match) == NULL) ||
    (CU_add_test(my_test_suite, " has key test\n", test_has_key) == NULL) ||
    (CU_add_test(my_test_suite, " has value test\n", test_has_value) == NULL) ||
    (CU_add_test(my_test_suite, " change all values test\n", test_change_all_values) == NULL) ||
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