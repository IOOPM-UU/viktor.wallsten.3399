#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "linked_list.h"
#include "common.h"

/**
 * @file hash_table.h
 * @author Anton Rodell, Viktor Wallsten
 * @date 15 Sep 2022
 * @brief Simple hash table that maps integer keys to string values.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 *
 * @see https://uppsala.instructure.com/courses/68435/assignments/130155
 */

typedef struct hash_table ioopm_hash_table_t;

//typedef bool(*ioopm_apply_function)(int key, char *value, void *extra);

/// @brief Create a new hash table
/// @return A new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create(ioopm_eq_function func, ioopm_hash_func hash_function);

/// @brief Delete a hash table and free its memory
/// @param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);

/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value);

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @param result adress of where to store the value mapped to by key 
/// @return if the lookup was succesful
bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key, elem_t*result);

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
///@param result adress of where to store the value mapped to by key 
/// @return a bool if the remove was succesfull or not
bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key, elem_t *result);

//--------------------ticket2-------------------

/// @brief returns the number of key => value entries in the hash table
/// @param h hash table operated upon
/// @return the number of key => value entries in the hash table
size_t ioopm_hash_table_size(ioopm_hash_table_t *ht);

/// @brief checks if the hash table is empty
/// @param h hash table operated upon
/// @return true is size == 0, else false
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht);

/// @brief clear all the entries in a hash table
/// @param h hash table operated upon
void ioopm_hash_table_clear(ioopm_hash_table_t *ht);

/// @brief return the keys for all entries in a hash map (in no particular order, but same as ioopm_hash_table_values)
/// @param h hash table operated upon
/// @return a linked list of keys for hash table h
ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht);

/// @brief return the values for all entries in a hash map (in no particular order, but same as ioopm_hash_table_keys)
/// @param h hash table operated upon
/// @return a linked list of values for hash table h which is nullterminated
ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *ht);

/// @brief check if a hash table has an entry with a given int key 
/// @param h hash table operated upon
/// @param key the key sought
bool ioopm_hash_table_has_key_int(ioopm_hash_table_t *ht, elem_t key);

/// @brief check if a hash table has an entry with a given string key 
/// @param h hash table operated upon
/// @param key the key sought
bool ioopm_hash_table_has_key_string(ioopm_hash_table_t *ht, elem_t key);

/// @brief check if a hash table has an entry with a given value
/// @param h hash table operated upon
/// @param value the value sought
bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value);

/// @brief check if a predicate is satisfied by all entries in a hash table
/// @param h hash table operated upon
/// @param pred the predicate
/// @param arg extra argument to pred
bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg);

/// @brief check if a predicate is satisfied by any entry in a hash table
/// @param h hash table operated upon
/// @param pred the predicate
/// @param arg extra argument to pred
bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg);

/// @brief apply a function to all entries in a hash table
/// @param h hash table operated upon
/// @param apply_fun the function to be applied to all elements
/// @param arg extra argument to apply_fun
void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function apply_fun, void *arg);

/// @brief checks if all keys in a ht is smaller than a given key
/// @param ht the hash table operated upon
/// @param key the given key
/// @return true if all the keys in the ht are smaller than key
bool ioopm_hash_table_all_key_smaller(ioopm_hash_table_t *ht, elem_t key);

/// @brief checks if all the values in a hash table is a given value
/// @param ht the hash table operated upon
/// @param value the value to compare
/// @return true if all the values in the hash table is equal to value
bool ioopm_hash_table_all_value(ioopm_hash_table_t *ht, elem_t value);



