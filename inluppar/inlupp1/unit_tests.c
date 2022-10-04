#include "hash_table.h"
#include "linked_list.h"
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


void test_create_destroy()
{
   ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL, NULL);
   CU_ASSERT_PTR_NOT_NULL(ht);
   ioopm_hash_table_destroy(ht);
}

void test_insert_once()
{
  
    ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_int, hash_func_int);              
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
    ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_int, hash_func_int);                     
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
  
    ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_int, hash_func_int);                     
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
   ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL, hash_func_int);
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
  
    ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_str, hash_func_string);                     
    char bar = 'b';
    elem_t k = ptr_elem("hejsan");                                                               
    elem_t v = int_elem(bar);
    elem_t result = ptr_elem(NULL);                                                  

    ioopm_hash_table_insert(ht, k, v);
    CU_ASSERT(ioopm_hash_table_has_key_string(ht, k));                                  
    CU_ASSERT(ioopm_hash_table_lookup(ht, k, &result));     
    CU_ASSERT(compare_int(result, v));             
    ioopm_hash_table_remove(ht, k, &result);
    CU_ASSERT(!ioopm_hash_table_lookup(ht, k, &result));
    ioopm_hash_table_destroy(ht);     
}


void test_remove_empty()
{
   elem_t v = ptr_elem(NULL);
   ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL, hash_func_int);
   for (int i = 0; i < No_buckets + 1; ++i) 
     {
       CU_ASSERT_PTR_NULL(ioopm_hash_table_remove(ht, int_elem(i), &v));
     }
   CU_ASSERT_PTR_NULL(ioopm_hash_table_remove(ht, int_elem(-1), &v));
   ioopm_hash_table_destroy(ht);
}

void test_table_size()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_int, hash_func_int);
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
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL, hash_func_int);
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  elem_t k = int_elem(0);                                                          
  elem_t v = ptr_elem("bar");                                                  
  ioopm_hash_table_insert(ht, k, v);
  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_destroy(ht);

}

void test_table_clear() 
{ 
  ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_int, hash_func_int);
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

  ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_int, hash_func_int);
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
  ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_str, hash_func_int);
  ioopm_hash_table_insert(ht, int_elem(7), ptr_elem("sju"));
  ioopm_hash_table_insert(ht, int_elem(15), ptr_elem("femton"));
  ioopm_list_t *values = ioopm_hash_table_values(ht);

  elem_t value1 = ioopm_linked_list_get(values, 0);
  elem_t value2 = ioopm_linked_list_get(values, 1);
  
  CU_ASSERT_FALSE(ioopm_linked_list_get(values, 3).i == 1);


  CU_ASSERT(compare_str(ptr_elem("sju"), value1));
  CU_ASSERT(compare_str(ptr_elem("femton"), value2));

  ioopm_linked_list_destroy(values);
  ioopm_hash_table_destroy(ht);

}

void test_check_value_and_keys_match()
{
int keys[5] = {3, 10, 42, 0, 99};


char *values[5] = {"three", "ten", "fortytwo", "zero", "ninetynine"};

ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_str, hash_func_int);
for (int i = 0; i < 5; ++i)
  {
    ioopm_hash_table_insert(ht, int_elem(keys[i]), ptr_elem(values[i]));
  }

  ioopm_list_t *found_keys = ioopm_hash_table_keys(ht);
  link_t *current = found_keys->first;



 ioopm_list_t *found_values = ioopm_hash_table_values(ht);

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
  
    ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_int, hash_func_int);              //create a new hashtable
    elem_t k = int_elem(0);                                                               //the key k
    elem_t v = ptr_elem("bar");                                                  //the value v
    CU_ASSERT_FALSE(ioopm_hash_table_has_key_int(ht, k));  
    ioopm_hash_table_insert(ht, k, v);                                  //insert the key k with the value value
    CU_ASSERT_TRUE(ioopm_hash_table_has_key_int(ht, k));                  //check that the key is in the table
    ioopm_hash_table_destroy(ht);
    
}

void test_has_value()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_int, hash_func_int);              //create a new hashtable
    elem_t k = int_elem(0);                                                               //the key k
    elem_t v = ptr_elem("bar");                                                  //the value v
    CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, v));
    ioopm_hash_table_insert(ht, k, v);                                
    CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, v));                 
                                                                      
    ioopm_hash_table_destroy(ht);                                           
}


void test_change_all_values()
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_int, hash_func_int);  
    for (int i = 0; i < 5; ++i)
    {
      ioopm_hash_table_insert(ht, int_elem(i), ptr_elem("bar"));
    }

    
    CU_ASSERT_TRUE(ioopm_hash_table_all_value(ht, ptr_elem("bar")));
    CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, ptr_elem("bar")));



    CU_ASSERT_FALSE(ioopm_hash_table_all_value(ht, ptr_elem("ba")));
    CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, ptr_elem("ba")));


    CU_ASSERT_TRUE(ioopm_hash_table_all_key_smaller(ht, int_elem(10)));
    CU_ASSERT_TRUE(ioopm_hash_table_has_key_int(ht, int_elem(2)));



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

    ioopm_hash_table_destroy(ht);                                           //clear the memory used by the table
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
    ioopm_linked_list_insert(list, 4, int_elem(7));


    
    ioopm_linked_list_remove(list, 0);
    ioopm_linked_list_remove(list, 2);
    ioopm_linked_list_remove(list, 1);
    ioopm_linked_list_remove(list, 1);
    ioopm_linked_list_remove(list, 0);
    
    CU_ASSERT_FALSE(ioopm_linked_list_remove(list, -1).i == 1);
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
  elem_t value = int_elem(2);

  for (int i = 0; i < 5; i++)
  {
    ioopm_linked_list_insert(list, i, value);
  }
  
  int new = 3;

  ioopm_linked_list_apply_to_all(list, change_elem, &new);

  CU_ASSERT_TRUE(ioopm_linked_list_contains(list, int_elem(3)));

  ioopm_linked_list_destroy(list);
}

void linked_list_any()
{
  ioopm_list_t *list = ioopm_linked_list_create(compare_int);
  ioopm_linked_list_insert(list, 0, int_elem(0));
  ioopm_linked_list_insert(list, 0, int_elem(1));
  ioopm_linked_list_insert(list, 0, int_elem(2));
  ioopm_linked_list_insert(list, 0, int_elem(3));
  ioopm_linked_list_insert(list, 0, int_elem(4));

  int check = 2;
  CU_ASSERT(ioopm_linked_list_any(list, values_eq_ll, &check));

  ioopm_linked_list_destroy(list);
}

void linked_list_all()
{
  ioopm_list_t *list = ioopm_linked_list_create(compare_int);
  ioopm_linked_list_insert(list, 0, int_elem(2));
  ioopm_linked_list_insert(list, 0, int_elem(2));
  ioopm_linked_list_insert(list, 0, int_elem(2));
  ioopm_linked_list_insert(list, 0, int_elem(2));
  ioopm_linked_list_insert(list, 0, int_elem(2));

  int check = 2;
  CU_ASSERT(ioopm_linked_list_all(list, values_eq_ll, &check));

  ioopm_linked_list_destroy(list);
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
    (CU_add_test(my_test_suite, "A insert test\n", test_insert) == NULL) ||
    (CU_add_test(my_test_suite, "A destroy test\n", test_linked_list_create_destroy) == NULL) ||
    (CU_add_test(my_test_suite, "A remove test\n", test_link_remove) == NULL) ||
    (CU_add_test(my_test_suite, "A prepend test\n", test_prepend) == NULL) ||
    (CU_add_test(my_test_suite, "A lookup test\n", test_lookup) == NULL) ||
    (CU_add_test(my_test_suite, "A size test\n", test_size) == NULL) ||
    (CU_add_test(my_test_suite, "A empty test\n", test_empty) == NULL) ||
    (CU_add_test(my_test_suite, "A apply to all\n", apply_to_all_test) == NULL) ||
    (CU_add_test(my_test_suite, "A all test\n", linked_list_all) == NULL) ||
    (CU_add_test(my_test_suite, "A all test\n", linked_list_any) == NULL) ||
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