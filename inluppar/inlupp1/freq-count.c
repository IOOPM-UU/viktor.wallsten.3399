#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash_table.h"
#include "linked_list.h"
#include "common.h"

#define Delimiters "+-#@()[]{}.,:;!_—&/<=>*!'$§?åäöéü \t\n\r"  

static int cmpstringp(const void *p1, const void *p2)
{
  return strcmp(*(char *const *)p1, *(char *const *)p2);
}

void sort_keys(char *keys[], size_t no_keys)
{
  qsort(keys, no_keys, sizeof(char *), cmpstringp);
}

void process_word(char *word, ioopm_hash_table_t *ht)
{
  if (!ioopm_hash_table_has_key_string(ht, ptr_elem(word)))
  {
    char *current = strdup(word);
    ioopm_hash_table_insert(ht, ptr_elem(current), int_elem(1));
  }
  else{
    elem_t result;
    ioopm_hash_table_lookup(ht, (elem_t) {.p = word}, &result);
    result.i++;
    ioopm_hash_table_insert(ht, ptr_elem(word), result);
  }
}

void process_file(char *filename, ioopm_hash_table_t *ht)
{
  FILE *f = fopen(filename, "r");
  while (true)
  {
    char *buf = NULL;
    size_t len = 0;
    getline(&buf, &len, f);
    if (feof(f))
    {
      free(buf);
      break;
    }
    for (char *word = strtok(buf, Delimiters); word && *word; word = strtok(NULL, Delimiters))
    {
      process_word(word, ht);
    }
    free(buf);
  }
  
  fclose(f);
}

int string_sum_hash(elem_t e)
{
  char *str = e.p;
  int result = 0;
  do
    {
      result += *str;
    }
  while (*++str != '\0');
  return result % 17;
}

bool string_eq(elem_t e1, elem_t e2)
{
  return (strcmp(e1.p, e2.p) == 0);
}

int main(int argc, char *argv[])
{
elem_t result = ptr_elem(NULL);
ioopm_hash_table_t *ht = ioopm_hash_table_create(string_eq, string_sum_hash);
  if (argc > 1)
  {
    for (int i = 1; i < argc; ++i)
    {
      process_file(argv[i], ht);
    } 

    ioopm_list_t *list = ioopm_hash_table_keys(ht);
    char **arr = calloc(list->size, sizeof(link_t));
    link_t *link = list->first;  
    int index = 0;
    while (link != NULL)
    {
        arr[index] = link->element.c;
        link = link->next;
        index++;
    }
    char **keys = arr;
    int size = ioopm_hash_table_size(ht);
    sort_keys(keys, size);

    for (int i = 0; i < size; ++i)
    {
      ioopm_hash_table_lookup(ht, (elem_t) {.p = keys[i]}, &result);
      int freq = result.i;
      printf("%s: %d\n", i[keys], freq);
    }

    for(int i = 0; i < list->size; i++ )
    {
      free(keys[i]);
    }

    ioopm_linked_list_destroy(list);
    free(arr);
  }
  else
  {
    puts("Usage: freq-count file1 ... filen");
  }
  // FIXME: Leaks memory! Use valgrind to find out where that memory is 
  // being allocated, and then insert code here to free it.

  ioopm_hash_table_destroy(ht);
}