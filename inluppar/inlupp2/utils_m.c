//
// Created by Matilda Sundberg on 2022-08-31.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "utils_m.h"
#include <stdbool.h>
#include <ctype.h>

bool is_shelf(char *str)
{
    if (isalpha(str[0])) ///fixa för en bokstav
    {
        for ( int i = 1; i < strlen(str)-1 ; i = i + 1)
        {
            if (!isdigit(str[i]))
            {
                return false;
            }
        }

    }
    else
        return false;

    return true;
}

answer_t to_upper (char *a)
{
    answer_t b;
    b.char_value = *a;
    b.char_value = toupper(b.char_value);
    return b;
}

bool is_number(char *str)
{
    for ( int i =  0; i < strlen(str); i = i + 1)
    {
        if (str[0] == '-' && i == 0)
        {
            i = i + 1;
        }
        if (!isdigit (str[i]))
        {
            return false;
        }
    }
    return true;
}

/// Hjälpfunktion till ask_question_string
bool not_empty(char *str)
{
    return strlen(str) > 0;
}

answer_t ask_question(char *question, check_func check, convert_func convert) {
    char buff[255];
    int s = 0;
    while (s < 1 || !check(buff)) {
        printf("%s\n", question);
        s = read_string(buff, 255);
    }
    return convert(buff);
}

char *ask_question_string(char *question)
{
    return ask_question(question, not_empty, (convert_func) strdup).string_value;
}

int ask_question_int(char *question)
{
    answer_t answer = ask_question(question, is_number, (convert_func) atoi);
    return answer.int_value; // svaret som ett heltal
}

char *ask_question_shelf(char *question)
{
    return ask_question(question, is_shelf,(convert_func) strdup ).string_value;
}

void print_menu(void)
{
    printf(" \n[A]dd merchandise \n [L]ist merchandise \n [R]emove merchandise \n [E]dit merchandise \n [S]how stock \n Re[p]lenish \n [C]reate cart \n Re[m]ove cart \n Add [t]o cart \n Remo[v]e from cart \n Calculate c[o]st \n C[h]eckout \n [Q]uit \n Pri[n]t cart\n");

}

bool check_menu(char *c)
{
    char *str = "AaLlRrEeSsPpCcMmTtVvOoQqHhNn";
    char *a = strchr(str, c[0]);
    if (a == NULL || strlen(c)>1 )
    {return false;}
    else
        return true;
}

char ask_question_menu(char *question)
{
    print_menu();
    char choice = ask_question(question, check_menu,(convert_func) to_upper ).char_value;
    return choice;
}

void print( char *strr)
{
    int i = 0;
    while (strr[i] != '\0')
    {
        putchar(strr[i]);
        i++;
    }
}

void println(char *string)
{
    print(string);
    print(" \n");
}


void clear_input_buffer()
{
    int c;
    do
    {
        c = getchar();
    }
    while (c != '\n' && c != EOF);
}


int read_string (char *buf, int buf_siz)
{
    char b;
    int p = 0;
    do
    {
        b = getchar();
        if(b != '\n')
        {
            buf [p] = b;
            p = p + 1;
        }
    }
    while (b != '\n' && b != EOF && p + 1 < buf_siz);
    if (p + 1 == buf_siz)
    {
        clear_input_buffer();
    }
    buf [p] = '\0';
    return p;
}


answer_t make_float(char *str)
{
    answer_t a;                // skapa ett oinitierat answer_t-värde
    a.float_value = atof(str); // gör det till en float, via atof
    return a;                  // returnera värdet
}