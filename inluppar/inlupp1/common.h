#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define No_buckets 17

#define int_elem(x) (elem_t) { .i=(x) }
#define ptr_elem(x) (elem_t) { .p=(x) }
#define bool_elem(x) (elem_t) { .b=(x)}

typedef union elem elem_t;
typedef bool (*ioopm_predicate)(elem_t key, elem_t value, void *extra);
typedef void (*ioopm_apply_function)(elem_t key, elem_t *value, void *extra);
typedef bool (*ioopm_eq_function)(elem_t a, elem_t b);
typedef int (*ioopm_hash_func)(elem_t a);

/// @brief comapre two elem_t that are interpreted as strings
/// @param a the elem_t you want to compare
/// @param b the elem_t you want to compare
/// @return true if a == b
bool compare_str(elem_t a, elem_t b);

/// @brief compare two elem_t that are interpreted as ints
/// @param a the elem_t you want to compare
/// @param b the elem_t you want to compare
/// @return true if a == b
bool compare_int(elem_t a, elem_t b);

/// @brief a hash function for when keys are ints
/// @param a a key that the hash function will be applied to
/// @return a hashed key
int hash_func_int(elem_t a);

/// @brief a hash function for when keys are strings
/// @param e a key that the hash function will be applied to
/// @return a hashed key
int hash_func_string(elem_t e);

/// @brief changes the value of value, if value is a string
/// @param key is ignored
/// @param value the old value
/// @param extra the new value
void change_values_str(elem_t key, elem_t *value, void *extra);

/// @brief changes the value value
/// @param index ignored
/// @param value the value to be changed
/// @param x the new value
void change_elem(int index, elem_t *value, void *x);

/// @brief compares the values of value and extra
/// @param index_ignored ignored
/// @param value value to be compared
/// @param extra value to be compared
/// @return true if value == extra
bool values_eq_ll(int index_ignored, elem_t value, void *extra);

union elem
{
    int i;
    unsigned int u;
    bool b;
    float f;
    void *p;
    char *c;
};

