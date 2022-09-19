#include "hash_table.h"


typedef struct entry entry_t;

struct entry
{
  int key;       // holds the key
  char *value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  entry_t buckets[No_buckets];
  int size; //holds the size of the table(number of entrys)
};

ioopm_hash_table_t *ioopm_hash_table_create()
{
  /// Allocate space for a ioopm_hash_table_t = No_buckets pointers to
  /// entry_t's, which will be set to NULL
  ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
  result->size = 0;
  return result;
}

/// @brief calculates the buckets index of a key
/// @param key key to map
/// @param bucket which bucket the key goes to

static int bucket_for_key(int key)
{
  int bucket = key % No_buckets;        // key mod (number of buckets) will give an index of |number of buckets| =< number of buckets
  if(bucket < 0)
  {
    bucket = bucket + No_buckets;      //if the index was negative we need to add No_buckets so it becomes positve for it to be interpreted correctly 
  }
  return bucket;
}


void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) 
{
  ioopm_hash_table_clear(ht);
  free(ht);                                     //free the memory alloceted to the table
}

static entry_t *find_previous_entry_for_key(entry_t *entry, int key)
{
  while (entry->next != NULL)
  {
    if(entry->next->key >= key)                   //true when our key is smaller or equal to the entry's key
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

static void *entry_create(int key, char *value, entry_t *next)
{
  entry_t *new = calloc(1, sizeof(entry_t));
  new->key = key;
  new->value = value;
  new->next = next;
  return new;
}


void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value)
{
  /// Calculate the bucket for this entry
  int bucket = bucket_for_key(key);

  /// Search for an existing entry for a key
  entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket], key);
  entry_t *next = entry->next;

  /// Check if the next entry should be updated or not
  if (next != NULL && next->key == key)
    {
      next->value = value;
    }
  else
    {
      entry->next = entry_create(key, value, next);
      ht->size += 1;
    }
}

bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key, char **result)
{
    /// Calculate the bucket for this entry
  int bucket = bucket_for_key(key);
  
  /// Find the previous entry for key
  entry_t *previous_entry = find_previous_entry_for_key(&ht->buckets[bucket], key);
  entry_t *next = previous_entry->next;

  if (next && next->key == key)
    {
      /// If entry was found, save its value at result... and return true
      *result = next->value;
      return true;
    }
  else
    {
      // if the entry wasn't found return false
      return false; 
    }
}

char *ioopm_call_lookup(ioopm_hash_table_t *ht, int key)
{
  char *result = NULL;
  bool success = ioopm_hash_table_lookup(ht, key, &result);
  if (success)
  {
    // success => result was updated
    //printf("key %d maps to %s!\n", key, result);
    return result;
  }
  else
  {
    // !success => result == NULL
    printf("key %d does not map to anything!\n", key);
    return NULL;
  }
}
bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key, char **result)
{
    /// Calculate the bucket for this entry
    int bucket = bucket_for_key(key);

    /// Search for an existing entry for a key
    entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket], key);
    entry_t *next = entry->next;
    
    if (next && next->key == key)
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

char *ioopm_call_remove(ioopm_hash_table_t *ht, int key)
{
  char *result = NULL;
  bool success = ioopm_hash_table_lookup(ht, key, &result);
  if (success)
  {
    // success => result was updated
    printf("key %d maps to %s, and was removed!\n", key, result);
    return result;
  }
  else
  {
    // !success => result == NULL
    printf("key %d does not map to anything!\n", key);
    return NULL;
  }
}


int ioopm_hash_table_size(ioopm_hash_table_t *ht)
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
      //current->next = NULL;
  }
  //ht->size = 0;
}

int *ioopm_hash_table_keys(ioopm_hash_table_t *ht)
{
  int *keys = calloc(1, sizeof(int[ioopm_hash_table_size(ht)]));
  int j = 0;
  for (int i = 0; i < No_buckets; i++)
  {                   
    entry_t *current =  ht->buckets[i].next;    // we intilize current to the first actual item in the list, the one linked from the dummy
    while(current != NULL)                      //while the next is't null we enter the loop
    {
      keys[j] = current->key;
      current = current->next;                  //update current to the next item
      j++;
    }
  }

  return keys;
}

//strlen() 
char **ioopm_hash_table_values(ioopm_hash_table_t *ht)
{
  char **values = calloc(ht->size, sizeof(char *));
  int j = 0;
  for (int i = 0; i < No_buckets; i++)
  {                   
    entry_t *current =  ht->buckets[i].next;    // we intilize current to the first actual item in the list, the one linked from the dummy
    while(current != NULL)                      //while the next is't null we enter the loop
    {
      values[j] = current->value;
      current = current->next;                  //update current to the next item
      j++;
    }
  }
  char **result = calloc(1, sizeof(values));

  for (int i = 0; i < ioopm_hash_table_size(ht); i++)
  {
    result[i] = values[i];
  }
  
  return result;
}

void change_values_str(int key, char **value, void *extra)
{
    *value = extra;
}



bool key_equiv(int key, char *value_ignored, void *x)
{
  int *other_key_ptr = x;
  int other_key = *other_key_ptr;
  return key == other_key;
  //return key == *((int *)x);
}

bool key_smaller(int key, char *value_ignored, void *x)
{
  int *other_key_ptr = x;
  int other_key = *other_key_ptr;
  return key < other_key;
  //return key == *((int *)x);
}


bool value_equiv(int key_ignored, char *value, void *x)
{
  /*char **other_value_ptr = x;
  char *other_value = *other_value_ptr;
  return !(strcmp(value, other_value));*/
  return !strcmp(value, *((char **)x));
}


bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, int key)
{
  return ioopm_hash_table_any(ht, key_equiv, &key);
}


bool ioopm_hash_table_all_key_smaller(ioopm_hash_table_t *ht, int key)
{
  return ioopm_hash_table_all(ht, key_smaller, &key);
}


bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, char *value)
{
    return ioopm_hash_table_any(ht, value_equiv, &value);
}


bool ioopm_hash_table_all_value(ioopm_hash_table_t *ht, char *value)
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
/*
void call_all()
{
    return ioopm_hash_table_all(ht, value_equiv, &value);

}

bool key_or_value()
{
    return ioopm_hash_table_has_value || ioopm_hash_table_has_key
}
    
*/

//typedef void(*ioopm_apply_function)(int key, char **value, void *extra)


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
