#include "common.h"
#include <stdlib.h>
#include <stdbool.h>



bool compare_int(elem_t a, elem_t b)
{
    return((a.i - b.i) == 0);
}

bool compare_str(elem_t a, elem_t b)
{
    return(strcmp(a.p, b.p) == 0);
}


int hash_func_int(elem_t a)
{
    a.i = a.i % No_buckets;
    if(a.i < 0)
    {
        a.i = a.i + No_buckets;
    }
    return a.i;
   
}


int hash_func_string(elem_t e)
{
  char *str = e.p;
  int result = 0;
  do
    {
      result += *str;
    }
  while (*++str != '\0');
  return result % No_buckets;
}