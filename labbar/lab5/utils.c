#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

extern char *strdup(const char *);

typedef union { 
  int   int_value;
  float float_value;
  char *string_value;
} answer_t;

typedef bool (*check_func)(char *); // deklaration av function check_func som tar en string och ger en bool

typedef answer_t (*convert_func)(char *); // deklaration av function check_func som tar en sträng och ger ett awnser


int ask_questions_int(char *question)
{
  int result = 0;
  int conversions = 0;
  do
    {
      printf("%s", question);
      conversions = scanf("%d", &result);
      int c;
      do
        {
          c = getchar();
        }
      while (c != '\n');
    }
  while (conversions < 1);
  return result;
}


int read_string(char *buf, int buf_siz) // vi får en en size och en tom array
{
  int aux = 0;
  int input;

 while(aux < (buf_siz -1) && (input = getchar()) != '\n') // måste vara buf_siz -1 eftersom det måste finnas plats för null-tecken, avbryter då 
  { 
  buf[aux] = input; // ittererar genom buf beroende på aux
  aux++;
  }

  buf[aux] = '\0'; // lägg till null-tecken

  return (aux);
}
 

bool is_number(char *str)
{
  int leng = strlen(str); // längden av input
  
 for (int i = 0; i < leng; i++) // går succsesivt igenom input 
 {
    if (!isdigit(str[i])) // om vi har en input där det endast är siffror så kommer if satsen aldrig att köras och vi returnar true, om det är en bokstav i input körs if-satsen och vi returnar fa
    {
        return false;
    }
 }
 return true;
}

void print( char *input)
{
    int i = 0;

    while(input[i] != '\0')
    {
        putchar(input[i]);
        i++;
    }

}

void println(char *input)
{
    print(input);
    print("\n");
}

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

    } while (count < 1);

    return convert(buf);
}

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

char *ask_question_string(char *question)
{
  return ask_question(question, not_empty, (convert_func) strdup).string_value;
}

bool is_shelf(char *str)
{
  int leng = strlen(str); // längden av input
  while(leng<3)
  {
    printf("Shelf must be atleast 3 characters long\n");
    return 0;
  }
  
 for (int i = 1; i < leng; i++) // går succsesivt igenom input 
 {
    if(!isalpha(str[0]))
    {
        printf("Wrong format\n");
        return false;
    }
    else
    {
        if (!isdigit(str[i]))
        { 
            printf("Wrong format\n");
            return false;
        }
    }
 }
 return true;
}

char *ask_question_shelf(char *question)
{
    return ask_question(question, (check_func) is_shelf, (convert_func) strdup).string_value;

}

struct item
{
    char *name;
    char *descript;
    char *shelf;
    int price; //OBS: I ören!
    
};

typedef struct {
    char *name;
    char *descript;
    char *shelf;
    int price;
} item_t;



void print_item(item_t *item)
{
    int sek = item->price / 100;
    int ore = item->price % 100;
    printf("NAME: %s\nDESC: %s\nPRICE: %d.%02d SEK \nSHELF: %s\n", item->name, item->descript, sek, ore, item->shelf);
}

item_t make_item(char *n, char *d, int p, char *s)
{
    item_t n_item = {.name = n, .descript = d, .price = p, .shelf =s};
    return n_item;
}

item_t input_item()
{
    char *item = ask_question_string("Please add your item: ");
    char *descript = ask_question_string("Please add an description to your item: ");
    int price = ask_questions_int("Please add a price to your item: ");
    char *shelf = ask_question_shelf("Place it in a shelf: ");
    item_t n_item = make_item(item, descript, price, shelf);
    return n_item;

}


char *magick(char *arr1[], char *arr2[], char *arr3[], int slump)
{
    char buf[255];
    int i = 0;
    int k = 0;
    int j = 0;

    
    i = (rand() % slump);

    k = (rand() % slump);

    j = (rand() % slump);

    snprintf(buf, sizeof(buf),"%s-,%s' ',%s", arr1[i], arr2[k], arr3[j]);

    return strdup(buf);
}

void list_db(item_t *items, int no_items)
{
    for(int i = 0; i < no_items; i++)
    {
        printf("%d) %s\n",i, items[i].name);
    }
}

item_t *edit_db(int db_size, item_t *items)
{

    int index = ask_questions_int("enter a item");

    while(index > db_size)
    {
        printf("out of bounds");
        return edit_db(db_size, items);
    }  

    print_item(&items[index]); 

    item_t new_item = input_item("please enter a new item: ");

    items[index] = new_item;

    return items;
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

void remove_item_from_db(item_t *db, int db_siz)
{
    list_db(db,db_siz);
    int c = ask_questions_int("enter the index of the item you wish to remove: ");

    while(c < 0 || c > (db_siz-1))
    {
    printf("invalid input\n");
    c = ask_questions_int("enter the index of the item you wish to remove: ");
    }

    if(c != db_siz)
    {
        
        for(; c < db_siz; c++)
         {  
            if(c == (db_siz -1))
            {
                db[c]= make_item("empty", "N/A", 0, "N/A");
            }
            else
            {
            db[c] = db[c+1]; 
            }
         }
    }
    
}

void add_item_to_db(int db_siz, item_t *db)
{
    item_t new_item = input_item("add a new item: ");
    if(db_siz == 0)// om vi har en tom aray
    {
        db[db_siz] = new_item;
    }
    db[db_siz++] = new_item;
}



void event_loop(item_t *db, int db_siz)
{
    char ans = ask_question_menu();

    if(ans == 'L')
    {
        add_item_to_db(db_siz, db);
    }
    else if(ans == 'T')
    {
        remove_item_from_db(db, db_siz);
    }
    else if( ans == 'R')
    {
        edit_db(db_siz, db);
    }
    else if(ans == 'G')
    {
        printf("not yet implemented\n");
    }
    else if(ans == 'H')
    {
        list_db(db, db_siz);
    }
    else if(ans == 'A')
    {
        printf("goodby\n");
    }
    else{
        printf("invalid input\n");
    }


}