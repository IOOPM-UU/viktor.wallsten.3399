#include "hash_table.h"

typedef struct entry entry_t;

struct entry
{
  elem_t key;       // holds the key
  elem_t value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  entry_t buckets[No_buckets];
  size_t size; //holds the size of the table(number of entrys)
  ioopm_eq_function func;
  ioopm_hash_func hash_function;
};


ioopm_hash_table_t *ioopm_hash_table_create(ioopm_eq_function func, ioopm_hash_func hash_function)
{
  /// Allocate space for a ioopm_hash_table_t = No_buckets pointers to
  /// entry_t's, which will be set to NULL
  ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
  result->size = 0;
  result->func = func;
  result->hash_function = hash_function;
  return result;
}

/// @brief calculates the buckets index of a key
/// @param key key to map
/// @param bucket which bucket the key goes to


void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) 
{
  ioopm_hash_table_clear(ht);
  free(ht);                                     //free the memory alloceted to the table
}

static entry_t *find_previous_entry_for_key(entry_t *entry, elem_t key, ioopm_hash_table_t *ht)
{
  while (entry->next != NULL)
  {
    if(ht->func(entry->next->key, key))                   //true when our key is smaller or equal to the entry's key
    {
      return entry;                               //return the current entry's key, which is > than the key argument
    }
    else
    {
      entry = entry->next;                         //iterate to the next entry
    }
  }
  return entry;                                     //returns an entry
}

static void *entry_create(elem_t key, elem_t value, entry_t *next)
{
  entry_t *new = calloc(1, sizeof(entry_t));
  new->key = key;
  new->value = value;
  new->next = next;
  return new;
}


void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value)
{
  /// Calculate the bucket for this entry
  int bucket = ht->hash_function(key);

  /// Search for an existing entry for a key
  entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket], key, ht);
  entry_t *next = entry->next;

  /// Check if the next entry should be updated or not
  if (next != NULL && ht->func(next->key, key))
    {
      next->value = value;
    }
  else
    {
      entry->next = entry_create(key, value, next);
      ht->size += 1;
    }
}

bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key, elem_t *result)
{
    /// Calculate the bucket for this entry
  int bucket = ht->hash_function(key);
  
  /// Find the previous entry for key
  entry_t *previous_entry = find_previous_entry_for_key(&ht->buckets[bucket], key, ht);
  entry_t *next = previous_entry->next;

  if (next && ht->hash_function(next->key) == ht->hash_function(key))
    {
      /// If entry was found, save its value at result... and return true
      *result = next->value;
      return true;
    }
  else
    {
      return false; // if the entry wasn't found return false
    }
}

bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key, elem_t *result)
{
    /// Calculate the bucket for this entry
    int bucket = ht->hash_function(key);

    /// Search for an existing entry for a key
    entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket], key, ht);
    entry_t *next = entry->next;
    
    if (next && ht->hash_function(next->key) == ht->hash_function(key))
      {
          entry->next = next->next;
          *result = next->value;
          free(next);
          ht->size -= 1;
          return true;
      }
    else
    {
        return false;
    }
}

size_t ioopm_hash_table_size(ioopm_hash_table_t *ht)
{
  return ht->size;
}

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
  return ioopm_hash_table_size(ht) == 0;
}


void ioopm_hash_table_clear(ioopm_hash_table_t *ht)
{
  for (int i = 0; i < No_buckets; i++)
  {                   
    entry_t *current =  ht->buckets[i].next;    // we intilize current to the first actual item in the list, the one linked from the dummy
    while(current != NULL)                      //while the next is't null we enter the loop
    {
      entry_t *temp = current;                  //save the current to a temporary 
      current = current->next;                  //update current to the next item
      free(temp);                               //free the memory allocated to preivous current(now temp) 
      ht->size -= 1;
    }
  }
}

ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht)
{
  ioopm_list_t *keys = ioopm_linked_list_create(NULL);
  for (int i = 0; i < No_buckets; i++)
  {                   
    entry_t *current =  ht->buckets[i].next;    // we intilize current to the first actual item in the list, the one linked from the dummy
    while(current != NULL)                      //while the next isn't null we enter the loop
    {
      ioopm_linked_list_append(keys, current->key); // append current key to the ll keys
      current = current->next;                  //update current to the next item
      
    }
  }

  return keys; // return the ll keys
}

//strlen() 
ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *ht)
{
ioopm_list_t *values = ioopm_linked_list_create(NULL);  
  for (int i = 0; i < No_buckets; i++)
  {                   
    entry_t *current =  ht->buckets[i].next;    // we intilize current to the first actual item in the list, the one linked from the dummy
    while(current != NULL)                      //while the next is't null we enter the loop
    {
      ioopm_linked_list_append(values, current->value);
      current = current->next;                  //update current to the next item
    }
  }
  
  return values;
}

 void change_values_str(elem_t key, elem_t *value, void *extra)
{
  elem_t *val = extra;
  *value = *val; 
}


bool key_equiv(elem_t key, elem_t value_ignored, void *x)
{
  elem_t *other_key_ptr = x;
  int other_key = other_key_ptr->i;
  int comp_key = key.i;

  return (other_key == comp_key);
}


static bool key_eqiv_string(elem_t a, elem_t ignored_b, void *x)
{
  elem_t *other_key_ptr = x;
  char *other_key = other_key_ptr->p;
  char *comp_key = a.p;

  return (strcmp(comp_key, other_key)== 0);

}

static bool key_smaller(elem_t key, elem_t value_ignored, void *x)
{
  elem_t *other_key_ptr = x;
  int other_key = other_key_ptr->i;
  int comp_key = key.i;
  return comp_key < other_key;
}


static bool value_equiv(elem_t key_ignored, elem_t value, void *x)
{
  elem_t *other_value_ptr = x;
  char *other_value = other_value_ptr->c;
  return (strcmp(value.c, other_value) == 0);
}

bool ioopm_hash_table_has_key_int(ioopm_hash_table_t *ht, elem_t key) ///////////// FEL KAN INTE TA EMOT INT OCH STRING
{
  return ioopm_hash_table_any(ht, key_equiv, &key);
}

bool ioopm_hash_table_has_key_string(ioopm_hash_table_t *ht, elem_t key)
{
    return ioopm_hash_table_any(ht, key_eqiv_string, &key);
}

bool ioopm_hash_table_all_key_smaller(ioopm_hash_table_t *ht, elem_t key)
{
  return ioopm_hash_table_all(ht, key_smaller, &key);
}

bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value)
{
    return ioopm_hash_table_any(ht, value_equiv, &value);
}


bool ioopm_hash_table_all_value(ioopm_hash_table_t *ht, elem_t value)
{
    return ioopm_hash_table_all(ht, value_equiv, &value);
}

bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg)
{
    for (int i = 0; i < No_buckets; i++)            //ALL BUCKETS
    {
      entry_t *current =  ht->buckets[i].next;    // we intilize current to the first actual item in the list, the one linked from the dummy
      while(current != NULL)                      //while the next is't null we enter the loop
      {
        if(pred(current->key, current->value, arg))     //while hjälp function är true retrun true
        {
          return true;
        }
        current = current->next;                  //update current to the next item
      }
    }
    return false;
}


bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate pred, void *x)
{
    for (int i = 0; i < No_buckets; i++)        //all buckets
    {
      entry_t *current =  ht->buckets[i].next;    // we intilize current to the first actual item in the list, the one linked from the dummy
      while(current != NULL)                      //while the next is't null we enter the loop
      {
        if(pred(current->key, current->value, x))      //när hjälp functionen returnar true gåvidare till next
        {
          current = current->next;              //update current to the next item
        }
        else
        {
          return false;                       //om hjälpf returnar false retrunar all false
        }                 
      }
    }
    return true;
}

void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function apply_fun, void *arg)
{
    for (int i = 0; i < No_buckets; i++)
    {
      entry_t *current =  ht->buckets[i].next;    // we intilize current to the first actual item in the list, the one linked from the dummy
      while(current != NULL)                      //while the next is't null we enter the loop
      {
        //int key = current->key;
        //char *value = current->value;
        apply_fun(current->key, &current->value, arg);
        current = current->next;                  //update current to the next item
      }
    }
    
}

//typedef void(*ioopm_apply_function)(int key, char **value, void *extra);
