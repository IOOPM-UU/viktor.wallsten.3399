#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdbool.h>
#include <time.h>

typedef union { 
  int   int_value;
  float float_value;
  char *string_value;
} answer_t;

struct item
{
    char *name;
    char *descript;
    char *shelf;
    int price;
    
};

typedef struct {
    char *name;
    char *descript;
    char *shelf;
    int price;
} item_t;


typedef bool (*check_func)(char *);

typedef answer_t (*convert_func)(char *);

int read_string(char *buf, int buf_siz);

bool is_number(char *str);

bool not_empty(char *str);

answer_t ask_question(char *question, check_func check, convert_func convert);

char *ask_question_string(char *question);

int ask_questions_int(char *question);

void println(char *input);

void print( char *input);

void print_item(item_t *item);

item_t make_item(char *n, char *d, int *p, char *s);

item_t input_item();

char *ask_question_shelf(char *question);

bool is_shelf(char *str);

char *magick(char *arr1[], char *arr2[], char *arr3[], int slump);

void list_db(item_t *items, int no_items);

item_t *edit_db(int db_size, item_t *items);

void event_loop(item_t *db, int db_siz);

char ask_question_menu();

void remove_item_from_db(item_t *db, int db_siz);

void add_item_to_db(int db_siz, item_t *db);

bool is_correct(char *buf);

void print_menu();


#endif