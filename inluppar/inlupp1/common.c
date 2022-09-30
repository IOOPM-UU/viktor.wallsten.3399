#include "common.h"
#include <stdlib.h>
#include <stdbool.h>
#define No_buckets 17


bool compare_int(elem_t a, elem_t b)
{
    return((a.i - b.i) == 0);
}

bool compare_str(elem_t a, elem_t b)
{
    return(strcmp(a.p, b.p) == 0);
}

elem_t gt_eq_func_int(elem_t a, elem_t b)
{
    if(a.i >= b.i)
    {
        return a;
    }
    return b;
}

int hash_func(elem_t a)
{
    a.i = a.i % No_buckets;
    if(a.i < 0)
    {
        a.i = a.i + No_buckets;
    }
    return a.i;
   
}
