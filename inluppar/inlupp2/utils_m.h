//
// Created by Matilda Sundberg on 2022-09-02.
//


#ifndef IOOPM_LABS_UTILS_H
#define IOOPM_LABS_UTILS_H

#include <stdbool.h>
typedef union {
    int   int_value;
    float float_value;
    char *string_value;
    char char_value;
} answer_t;

typedef bool(*check_func)(char *);
typedef answer_t(*convert_func)(char *);
typedef int(*int_fold_func)(int, int);

bool is_shelf(char *str);
int read_string(char *buf, int buf_siz);
bool is_number(char *str);
int ask_question_int(char *question);
bool not_empty(char *str);
void clear_input_buffer();
char *ask_question_shelf(char *question);
answer_t ask_question(char *question, check_func check, convert_func convert);
char *ask_question_string(char *question);
int ask_question_int(char *question);
void print_menu(void);
bool check_menu(char *c);
char ask_question_menu(char *question);

extern char *strdup(const char *);

#endif //IOOPM_LABS_UTILS_H
