#define No_Buckets 17
#include "hash_table.h"
#include <stdlib.h>
#include <stdio.h>
#include <CUnit/Basic.h>
#include <stdbool.h>
#include <string.h>
#define Success(v)      (option_t) { .success = true, .value = v };
#define Failure()       (option_t) { .success = false };
#define Successful(o)   (o.success == true)
#define Unsuccessful(o) (o.success == false)

typedef struct entry entry_t;

struct entry
{
  int key;       // holds the key
  char *value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  entry_t *buckets[No_Buckets];
  int size;
};

static entry_t *entry_create(int k, char *value, entry_t *next)
{
  entry_t *new = calloc(1, sizeof(entry_t));
  new->key = k;
  new->value = value;
  new->next= next;
  return new;
}

int find_index(int key)
{
  int bucket = key % No_Buckets;

  if(bucket < 0)
  {
    bucket = bucket + No_Buckets;
  }
  return bucket;
}

ioopm_hash_table_t *ioopm_hash_table_create()
{
  /// Allocate space for a ioopm_hash_table_t = 17 pointers to
  /// entry_t's, which will be set to NULL
  ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
  for(int i = 0; i < No_Buckets; i++)
    {
    result->buckets[i] = entry_create(0, NULL, NULL);
    }
  result->size = 0;
  return result;
}

static entry_t *find_previous_entry_for_key(entry_t *buckets, int key)
{
  entry_t *first_entry = buckets; // första element i buckets
  entry_t *temp = first_entry; // en pointer till första elem i buckets

while(temp-> next != NULL) // kör så länge du inte står på sista elem i buckets
{
  if(temp->next-> key >= key) // kollar på elem efter temp och jämnför med key
  {
    return temp;
  }
  
  temp = temp->next; // går till nästa elem
  
}
return temp; //om vi kommer hit står vi längst bak och då ska det nya elem läggas till efter dvs det längst bak blir previous
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value)
{
  /// Calculate the bucket for this entry
  int bucket = find_index(key);
  /// Search for an existing entry for a key
  entry_t *entry = find_previous_entry_for_key(ht->buckets[bucket], key);
  entry_t *next = entry->next;

  /// Check if the next entry should be updated or not
  if (next != NULL && next->key == key)
    {
      next->value = value;
    }
  else
    {
      entry->next = entry_create(key, value, next);
      ht->size =+1;
    }
}

option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key) // resultat måste vara ** eftersom att det ska vara en pekare till en string, string  är en pointer så det blir pekare till pekare
{
  /// Find the previous entry for key
  entry_t *tmp = find_previous_entry_for_key(ht->buckets[find_index(key)], key);// vi hittar entry som är innan den vi vill hitta
  entry_t *next = tmp->next; //sätter next till den vi vill hitta

 if (next && (next->key == key)) // kollar om det existerar alltså inte är NULL och att det är den key:n vi vill hitta
  {
    return Success(next->value);
  }
else
  {
    return Failure();
  }
}

int *ioopm_hash_table_keys(ioopm_hash_table_t *ht)
{
  int *arr_key = calloc(ht->size,sizeof(int));
  int index = 0;

  for(int i = 0; i < No_Buckets; i ++) // will itterera genom alla våra buckets
  {
    entry_t *current = ht->buckets[i]; // ställer oss i den länkade listan på plats i

    while (current != NULL) // kör tills vi kommer sist i länkade listan
    {
      entry_t *temp = current->next;
      arr_key[index] = current->key;
      current = temp;
      index++;
    }
  }
return arr_key;

}

char **ioopm_hash_table_values(ioopm_hash_table_t *ht)
{
  char **arr_val = calloc(ht->size, sizeof(char *));
  int index = 0;

  for(int i = 0; i < No_Buckets; i++)
  {
    entry_t *current = ht->buckets[i];

    while(current != NULL)
    {
      entry_t *temp = current->next;
      arr_val[index] = current->value;
      current = temp;
      index++;
    }
  }
return arr_val;
}



void entry_destroy(entry_t *entry)
{
  free(entry);
}

void ioopm_hash_table_clear(ioopm_hash_table_t *ht)
{
  for(int i = 0; i < No_Buckets; i++)
  {
    entry_t *current = ht->buckets[i]; // tar in vår array buckets
  
    while (current != NULL) //kollar att entryn vi står i inte är tom
    {
      entry_t *temp = current->next; // sätter temp till elem efter current
      entry_destroy(current); // förstör den vi står i
      current = temp;// sätter current till nästa elem
    }
  }
    
}

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, int key)
{
  bool success = ioopm_hash_table_lookup(ht, key).success;
  return success;
}

bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, char *value)
{
  for(int i = 0; i < No_Buckets; i++)
  {
    entry_t *current= ht->buckets[i]->next; // behövde hoppas över dummy insert
    

    while(current != NULL)
    {
      if(strcmp(current->value, value) == 0) 
      {
        return true;
      }
      else
      {
        current = current->next;
        
      }
    }
  }
  return false;
}


void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) 
{
ioopm_hash_table_clear(ht); 
free(ht); // förstör hashtable
}

char *ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key)
{
  char *value = NULL;
  /// Find the previous entry for key
  entry_t *prev_rem = find_previous_entry_for_key(ht->buckets[find_index(key)], key);// vi hittar entry som är innan den vi vill hitta
  entry_t *rem = prev_rem->next; //sätter next till den vi vill hitta, next är den vi faktiskt vill ta bort

  if (rem && (rem->key == key)) // kollar att den existerar och att nästa är den vi vill ta bort
  {
    prev_rem->next = rem->next; // sätt pekaren på den innan den vi vill ta bort till pekaren som vi vill ta bort
    value = rem->value; // sätter value till värdet på noden vi vill ta bort
    free(rem); // gör free på den vi vill ta bort
    ht->size =- 1;
    return value;
  }
  else
  {
    printf("key does not exist\n");
  }
  
  return value;
}

int ioopm_hash_table_size(ioopm_hash_table_t *ht)
  {
  int storlek = ht->size;
  return storlek;
  }

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
  return ioopm_hash_table_size(ht) == 0;
}



 
 /*
 int main()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(); // skapa hash table
  int k = 0; // make key
  char *value = "bar";

  ioopm_hash_table_insert(ht, k, value);
  if(ioopm_hash_table_has_key(ht,k))
  {
    puts("works");
  }
  
  if(ioopm_hash_table_has_key(ht,78))
  {
    puts("78");
  }
  else{
    puts("works");
  }

  if (ioopm_hash_table_has_value(ht, value))
  {
    puts("works_s");
  }
  if(ioopm_hash_table_has_value(ht, "foo"))
  {
    puts("foo");
  }
  else {
    puts("works_s");
  }
  
  ioopm_hash_table_destroy(ht);
  return 0;

}
*/