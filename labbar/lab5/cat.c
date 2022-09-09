/// cat.c
#include <stdio.h>
#include "utils.h"
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

void cat(char *filename)
{
  FILE *f = fopen(filename, "r");
  int c = fgetc(f);
  int i = 1;
  
  printf("%d ", i);
  i++;

  while (c != EOF)
  {
    if (c == '\n')
    {
        printf("\n%d ", i);
        i++;
    }
    else{
        fputc(c, stdout); // tar det som finns i c och skriver till terminalen 
    }
    
    c = fgetc(f); // läser ett tecken från filen;
    
  }
  putchar('\n');
  fclose(f);
}

void print_menu()
{
    char *vara = "[L]ista en vara";
    char *ta_bort = "[T]a bort en vara";
    char *redigera = "[R]edigera en vara";
    char *angra = "ån[G]ra en vara";
    char *lista = "lista [H]ela varulistan";
    char *avsluta = "[A]vsluta";

    printf("%s\n%s\n%s\n%s\n%s\n%s\n", vara, ta_bort, redigera, angra, lista, avsluta);
}

bool is_correct(char *buf)
{
    char *arr= "LlTtRrGgHhAa";
    int c = strlen(arr);
    
    if((strlen(buf) > 1))
    {
        return false;
    }
    for(int i = 0; i < c; i++)
    {
        if(*buf == arr[i])
        {
            return true;
        }
    }
    return false;
}

void add_item_to_db(int *db_siz, item_t *db)
{
    item_t new_item = input_item("add a new item: ");
    if(*db_siz == 0)// om vi har en tom aray
    {
        db[*db_siz] = new_item;
    }
    db[*db_siz++] = new_item;
}

void remove_item_from_db(item_t *db, int db_siz)
{
    list_db(db,db_siz);
    int c = ask_questions_int("enter the index of the item you wish to remove: ");

    do{
    printf("invalid input");

    }while(c < 1 || c > db_siz);

    for(c; c < db_siz; c++);
    {
        if(c < db_siz)
        {
            db[c] = db[c+1];
        }
        else
        {
            db[db_siz]= make_item("empty", "N/A", 0, "N/A");
        }
    }
    db[db_siz]= make_item("empty", "N/A", 0, "N/A"); // tar och sätter varan längst bak till empty

}

char ask_question_menu()
{   
    int count = 0;
    int buf_siz = 255;
    char buf[buf_siz];
    
    do
    {
        print_menu();
        read_string(buf, buf_siz);
        if(is_correct(buf))
        {
            count++;
        }

    } while (count < 1);
    
    return toupper(*buf);
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    fprintf(stdout, "Usage: %s fil1 ...\n", argv[0]);
  }
  else
  {
    for (int i = 1; i < argc; ++i)
    {
      cat(argv[i]);
    }
  }

  ask_question_menu();
  return 0;
}