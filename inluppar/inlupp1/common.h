#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define int_elem(x) (elem_t) { .i=(x) }
#define ptr_elem(x) (elem_t) { .p=(x) }
#define bool_elem(x) (elem_t) { .b=(x)}

typedef union elem elem_t;
typedef bool (*ioopm_predicate)(elem_t key, elem_t value, void *extra);
typedef void (*ioopm_apply_function)(elem_t key, elem_t *value, void *extra);
typedef bool (*ioopm_eq_function)(elem_t a, elem_t b);
typedef int (*ioopm_hash_func)(elem_t a);


bool compare_str(elem_t a, elem_t b);
bool compare_int(elem_t a, elem_t b);
elem_t gt_eq_func_int(elem_t a, elem_t b);
int hash_func(elem_t a);


union elem
{
    int i;
    unsigned int u;
    bool b;
    float f;
    void *p;
    char *c;
};

