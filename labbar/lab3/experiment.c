#include <stdio.h>
#include "utils.h"
#include <string.h>
#include <stdlib.h>

extern char *strdup(const char *);


/// Hjälpfunktion till ask_question_string
bool not_empty(char *str)
{
  if (strlen(str) > 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

typedef union { 
  int   int_value;
  float float_value;
  char *string_value;
} answer_t;

typedef bool (*check_func)(char *); // deklaration av function check_func som tar en string och ger en bool

typedef answer_t (*convert_func)(char *); // deklaration av function check_func som tar en sträng och ger ett awnser

answer_t ask_question(char *question, check_func check, convert_func convert)
{   
    int count = 0;
    int buf_siz = 255;
    char buf[buf_siz];
    
    do
    {
        printf("%s", question);
        read_string(buf, buf_siz);
        if(check(buf))
        {
            count++;
        }
        else
        {
            printf("please add valid input\n");
        }

    } while (count < 1);

    return convert(buf);
}


char *ask_question_string(char *question)
{
  return ask_question(question, not_empty, (convert_func) strdup).string_value;
}

int main()
{
    printf("%d\n", ask_question("mata in ett nummer\n", is_number, (convert_func) atoi).int_value);
    printf("%s", ask_question_string("enter your name \n"));
    puts("\n");
    return 0;
}