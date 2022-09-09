#include <stdio.h>
#include "utils.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


extern char *strdup(const char *);



int main(int argc, char *argv[])
{
char *array1[] = { "Laser",        "Polka",    "Extra" };
char *array2[] = { "förnicklad",   "smakande", "ordinär" };
char *array3[] = { "skruvdragare", "kola",     "uppgift" };



srand(time(0));
  if (argc < 2)
  {
    printf("Usage: %s number\n", argv[0]);
  }
  else
  {
    item_t db[16]; // Array med plats för 16 varor
    int db_siz = 0; // Antalet varor i arrayen just nu

    int items = atoi(argv[1]); // Antalet varor som skall skapas

    if (items > 0 && items <= 16)
    {
      for (int i = 0; i < items; ++i)
      {
        // Läs in en vara, lägg till den i arrayen, öka storleksräknaren
        item_t item = input_item();
        db[db_siz] = item;
        ++db_siz;
      }
    }
    else
    {
      puts("Sorry, must have [1-16] items in database.");
      return 1; // Avslutar programmet!
    }

    for (int i = db_siz; i < 16; ++i)
      {
        char *name = magick(array1, array2, array3, 3); // TODO: Lägg till storlek
        char *desc = magick(array1, array2, array3, 3); // TODO: Lägg till storlek
        int price = random() % 200000;
        char shelf[] = { random() % ('Z'-'A') + 'A',
                         random() % 10 + '0',
                         random() % 10 + '0',
                         '\0' };
        item_t item = make_item(name, desc, &price, shelf);

        db[db_siz] = item;
        ++db_siz;
      }

     // Skriv ut innehållet
     
     //remove_item_from_db(db, db_siz);
     //add_item_to_db(db_siz, db);
     //list_db(db,db_siz);
     event_loop(db, db_siz);
     list_db(db, db_siz);

  }
  return 0;
}
