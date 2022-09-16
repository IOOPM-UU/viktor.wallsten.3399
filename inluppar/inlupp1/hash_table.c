#define No_Buckets 17
#include "hash_table.h"
#include <stdlib.h>
#include <stdio.h>
#include <CUnit/Basic.h>
#include <stdbool.h>
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
  int bucket = key % No_Buckets;
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



void entry_destroy(entry_t *entry)
{
  free(entry);
}


void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) {
  
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
    return value;
  }
  else
  {
    printf("key does not exist\n");
  }
  
  return value;
}
 
 /*
 int main()
{
   ioopm_hash_table_t *ht = ioopm_hash_table_create(); // skapa hash table
  int k = 0; // make key
  char *value = "bar";

  ioopm_hash_table_insert(ht, k, value);
  call_lookup(ht, k);
  ioopm_hash_table_remove(ht, 23);
  ioopm_hash_table_remove(ht, k);
  ioopm_hash_table_lookup(ht, k);
  return 0;

}
*/