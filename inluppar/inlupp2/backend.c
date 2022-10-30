#include "common.h"
#include "hash_table.h"
#include "linked_list.h"
#include "backend.h"
#include "utils_m.h"
#include "iterator.h"

void merch_clear(ioopm_warehouse_t *warehouse)
{
char **keys = ioopm_merch_list_no_print(warehouse);
for (int i = 0; i < ioopm_hash_table_size(warehouse->items); i++)
{
  elem_t key = ptr_elem(keys[i]);
  elem_t value = ptr_elem(NULL);
  ioopm_hash_table_lookup(warehouse->items, key, &value);
  merch_t *merch_to_clear = value.p;
  ioopm_list_t *location = merch_to_clear->location;

for (int j = 0; j < ioopm_linked_list_size(location); j++)//free alla shelves i location
  {
    elem_t shelf_to_remove = ioopm_linked_list_get(location, j);
    shelf_t *shelf = shelf_to_remove.p;
    free(shelf);
    shelf = NULL;
  }

  ioopm_linked_list_destroy(location);
  free(merch_to_clear);
}
ioopm_hash_table_clear(warehouse->shelves);
ioopm_hash_table_clear(warehouse->items);
free(keys);
keys = NULL;
}

shelf_t *shelf_create(elem_t name, elem_t quantity)
{
  shelf_t *shelf = calloc(1, sizeof(shelf_t));
  shelf->name = name;
  shelf->quantity = quantity;
  return shelf;
}

void ioopm_warehouse_destroy(ioopm_warehouse_t *warehouse)
{
  merch_clear(warehouse);
  ioopm_hash_table_destroy(warehouse->items);
  ioopm_hash_table_destroy(warehouse->shelves);
  free(warehouse);
  warehouse = NULL;
}


ioopm_warehouse_t *ioopm_warehouse_create(ioopm_eq_function func, ioopm_hash_func hash_function)
{
  ioopm_warehouse_t *warehouse = calloc(1, sizeof(ioopm_warehouse_t));
  warehouse->items = ioopm_hash_table_create(func, hash_function);
  warehouse->shelves = ioopm_hash_table_create(func, hash_function);
  return warehouse;
}

static merch_t *ioopm_merch_create(char *name, char *description, int price)
{
  ioopm_list_t *location = ioopm_linked_list_create(compare_str);
  merch_t *new  = calloc(1, sizeof(merch_t));

  new->name = name;
  new->description = description;
  new->price = price;
  new->location = location;
  return new;
}

void ioopm_merch_add(ioopm_warehouse_t *warehouse, char *name, char *description, int price)
{
  if(!ioopm_hash_table_is_empty(warehouse->items))
  {
    if(ioopm_hash_table_has_key_string(warehouse->items, ptr_elem(name)))
    {
      printf("item alredy in warehouse\n");
    }
    else
    {
      merch_t *new_merch = ioopm_merch_create(name, description, price);
      elem_t key = ptr_elem(new_merch->name);
      elem_t value = ptr_elem(new_merch);
      
      ioopm_hash_table_insert(warehouse->items, key, value);
    }
  }
  else
  {
      merch_t *new_merch = ioopm_merch_create(name, description, price);
      elem_t key = ptr_elem(new_merch->name);
      elem_t value = ptr_elem(new_merch);

      ioopm_hash_table_insert(warehouse->items, key, value);
  }
}

void ioopm_merch_list_merch(ioopm_warehouse_t *warehouse)
{
  ioopm_list_t *all_merch = ioopm_hash_table_keys(warehouse->items);
  link_t *link = all_merch->first;
  char **arr = calloc(ioopm_hash_table_size(warehouse->items), sizeof(link_t));
  int index = 0;
  while (link != NULL)
  {
    arr[index] = link->element.c;
    link = link->next;
    index++;
  }
  link = all_merch->first;
    while(link != NULL)
    {
      if(ioopm_hash_table_size(warehouse->items) < 20)
      {
        for(int i = 0; i < ioopm_hash_table_size(warehouse->items); i++)
        {
          printf("%d) %s\n", i, link->element.c);
          link = link->next;
        }
      }
    else
    {
      for(int i = 0; i < 20; i++)
      {
        printf("%d) %s \n", i, link->element.c);
        link = link->next; 
      }
    }
  }
  free(arr);
  ioopm_linked_list_destroy(all_merch);
}

char **ioopm_merch_list_no_print(ioopm_warehouse_t *warehouse)
{
  ioopm_list_t *all_merch = ioopm_hash_table_keys(warehouse->items);
  link_t *link = all_merch->first;
  char **arr =calloc(ioopm_hash_table_size(warehouse->items), sizeof(char*));
  int index = 0;
  while (link != NULL)
  {
    arr[index] = link->element.c;
    link = link->next;
    index++;
  }
  ioopm_linked_list_destroy(all_merch);
  return arr;
}

char **cart_list(ioopm_cart_t *cart)
{
ioopm_list_t *all_merch = ioopm_hash_table_keys(cart->cart_ht);
link_t *link = all_merch->first;
char **carr = calloc(ioopm_hash_table_size(cart->cart_ht), sizeof(char*));
int index = 0;
while (link != NULL)
{
  carr[index] = link->element.c;
  link = link->next;
  index++;
}
ioopm_linked_list_destroy(all_merch);
return carr;
}

void ioopm_remove_merch(ioopm_warehouse_t *warehouse, int index)
{
char **keys = ioopm_merch_list_no_print(warehouse);

elem_t key = ptr_elem(keys[index]);
elem_t value = ptr_elem(NULL);

ioopm_hash_table_lookup(warehouse->items, key, &value);
merch_t *merch_to_remove = value.p;
ioopm_list_t *location = merch_to_remove->location;

for (int i = 0; i < ioopm_linked_list_size(location); i++)
{
    elem_t shelf_to_remove = ioopm_linked_list_get(location, i);
    shelf_t *loc = shelf_to_remove.p;
    ioopm_hash_table_remove(warehouse->shelves, loc->name, &ptr_elem(NULL));
    free(loc);
    loc = NULL;
}
ioopm_linked_list_destroy(location);
free(merch_to_remove);
merch_to_remove = NULL;
ioopm_hash_table_remove(warehouse->items, key, &value);
free(keys);
}


merch_t *find_merch(ioopm_warehouse_t *warehouse, elem_t name)
{
if(ioopm_hash_table_has_key_string(warehouse->items, name))  
{
  elem_t result = ptr_elem(NULL);
  ioopm_hash_table_lookup(warehouse->items, name, &result);
  merch_t *merch = result.p;
  return merch;
}

return NULL;
}

void update_shelf(ioopm_warehouse_t *warehouse, ioopm_list_t *location, char *name)
{
   ioopm_list_iterator_t *iter = ioopm_list_iterator(location);
   shelf_t *shelf = ioopm_iterator_current(iter).p;
   ioopm_hash_table_insert(warehouse->shelves, shelf->name, ptr_elem(name));

   while (ioopm_iterator_has_next(iter))
   {
    ioopm_hash_table_insert(warehouse->shelves, shelf->name, ptr_elem(name));
    ioopm_iterator_next(iter, &ptr_elem(NULL));
   }
   ioopm_iterator_destroy(iter);
}

void ioopm_edit_merch(ioopm_warehouse_t *warehouse, char *merch_name, char *name, char *description, int price)
{                     
merch_t *to_be_edited = find_merch(warehouse, ptr_elem(merch_name));
if(!strcmp(to_be_edited->name, name))                       
  {
  to_be_edited->description = description;
  to_be_edited->price = price;
  return;
  }
merch_t *newmerch = ioopm_merch_create(name, description, price);
ioopm_linked_list_destroy(newmerch->location);
newmerch->location = to_be_edited->location;
ioopm_hash_table_remove(warehouse->items, ptr_elem(to_be_edited->name), &ptr_elem(NULL));
ioopm_hash_table_insert(warehouse->items, ptr_elem(newmerch->name), ptr_elem(newmerch));
update_shelf(warehouse, newmerch->location, newmerch->name);
free(to_be_edited);
}

void ioopm_add_stock(ioopm_warehouse_t *warehouse,char *merch_name, char *new_shelf, int quant)
{
  merch_t *merch = find_merch(warehouse, ptr_elem(merch_name));

  ioopm_list_t *location = merch->location;
  shelf_t *shelf = shelf_create(ptr_elem(new_shelf), int_elem(quant));
  ioopm_linked_list_append(location, ptr_elem(shelf));
  ioopm_hash_table_insert(warehouse->shelves, ptr_elem(new_shelf), ptr_elem(merch));
}

bool shelf_contains(ioopm_list_t *location, elem_t shelf_name)
{
link_t *current = location->first; // ställer mig i första länken

while (current != NULL) 
{
shelf_t *shelf = current->element.p;
if(location->func(shelf->name, shelf_name))
{
    return true;
}
else
{
    current = current->next;
}
}

return false;

}

void ioopm_replenish_stock(ioopm_warehouse_t *warehouse, char *name_merch , char *shelf_name, int quant)
{

merch_t *merch_to_edit = find_merch(warehouse, ptr_elem(name_merch));

ioopm_list_t *location = merch_to_edit->location;

if (shelf_contains(location, ptr_elem(shelf_name))) // om shelf finns
  {
  int i = 0;
  elem_t result = ioopm_linked_list_get(location, i);
  shelf_t *find_loc = result.p;
  char *find_shelf = find_loc->name.p;
  
  while(strcmp(find_shelf, shelf_name) != 0) //hitta hyllan vi vill förändra
  {
    i = i + 1;
    int i = 0;
    result = ioopm_linked_list_get(location, i);
    find_loc = result.p;
    find_shelf = find_loc->name.p;
  }
  int new_quant = find_loc->quantity.i;
  find_loc->quantity = int_elem(new_quant + quant);
  ioopm_hash_table_insert(warehouse->shelves, ptr_elem(shelf_name), ptr_elem(merch_to_edit)); 
  }
else
  {
    ioopm_add_stock(warehouse, name_merch, shelf_name, quant);
  }
}

int total_stock(ioopm_list_t *location)
{
  link_t *current_shelf = location->first;
  int total_quant = 0;
  while (current_shelf != NULL )
  {
    int quant = ((shelf_t*)current_shelf->element.p)->quantity.i;
    total_quant += quant;
    current_shelf = current_shelf->next;
  }
  return total_quant;
}

void ioopm_show_stock(ioopm_warehouse_t *warehouse, int index)
{
char **keys = ioopm_merch_list_no_print(warehouse);

elem_t merch_find =ptr_elem(keys[index]);
elem_t result = ptr_elem(NULL);

ioopm_hash_table_lookup(warehouse->items, merch_find, &result);
merch_t *found_merch = result.p;
ioopm_list_t *location = found_merch->location;

for (int i = 0; i < ioopm_linked_list_size(location); i++)
  {
    elem_t shelf_first = ioopm_linked_list_get(location, i);
    shelf_t *first_loc = shelf_first.p;
    printf("shelf: %s\nquantity: %d\n", first_loc->name.c, first_loc->quantity.i);
  }
int total_quant = total_stock(location);
printf("total stock: %d\n", total_quant);
free(keys); 
}

ioopm_cart_list_t *ioopm_cart_create_list()
{
  ioopm_cart_list_t *carts = calloc(1, sizeof(ioopm_cart_list_t));
  carts->all_carts = ioopm_linked_list_create(compare_str);
  return carts;
}

ioopm_cart_t *ioopm_create_cart(ioopm_cart_list_t *carts)
{
  ioopm_cart_t *cart = calloc(1, sizeof(ioopm_cart_t));
  cart->cart_int = ioopm_linked_list_size(carts->all_carts);
  cart->cart_ht = ioopm_hash_table_create(compare_str, hash_func_string);
  cart->sum = 0;
  ioopm_linked_list_append(carts->all_carts, ptr_elem(cart));
  return cart;
}

void  ioopm_remove_cart(ioopm_cart_t *cart)
{
  ioopm_hash_table_destroy(cart->cart_ht);
  free(cart);
}

void ioopm_cart_destroy(ioopm_cart_list_t *carts, int index)
{
  ioopm_cart_t *cart = ioopm_linked_list_get(carts->all_carts, index).p;
  ioopm_remove_cart(cart);
  ioopm_linked_list_remove(carts->all_carts, index);
}

void cart_nuke(ioopm_cart_list_t *carts)
{
  if(ioopm_linked_list_size(carts->all_carts) > 0)
  { 
    link_t *current = carts->all_carts->first;
    for (int i = 0; i < ioopm_linked_list_size(carts->all_carts); i++)
    {
      ioopm_remove_cart(current->element.p);
      current = current->next;
    }
  }
  ioopm_linked_list_destroy(carts->all_carts);
  free(carts);
}

void list_carts(ioopm_cart_list_t *carts)
{
  ioopm_list_t *tot_cart = carts->all_carts;

  for (int i = 0; i < ioopm_linked_list_size(tot_cart); i++)
  {
    ioopm_cart_t *cart = ioopm_linked_list_get(tot_cart, i).p;
    printf("%d)cart %d\n",i, cart->cart_int);
  }
}

void print_carts(ioopm_cart_t *cart)
{
  ioopm_list_t *keys = ioopm_hash_table_keys(cart->cart_ht);
  link_t *link = keys->first;
  char **arr = calloc(ioopm_hash_table_size(cart->cart_ht), sizeof(link_t));
  int index = 0;
  while (link != NULL)
  {
    arr[index] = link->element.c;
    link = link->next;
    index++;
  }
  for (int i = 0; i < ioopm_hash_table_size(cart->cart_ht); i++)
  {
    elem_t key = ptr_elem(arr[i]);
    elem_t value = ptr_elem(NULL);
    ioopm_hash_table_lookup(cart->cart_ht, key, &value);
    printf("\n%d) %s, %d\n",i, arr[i], value.i);
  }
  free(arr);
  ioopm_linked_list_destroy(keys);

}

bool item_in_cart(ioopm_cart_t *cart, char *name)
{
  bool succsess = ioopm_hash_table_lookup(cart->cart_ht, ptr_elem(name), &ptr_elem(NULL));
  return succsess;
}

void ioopm_add_to_cart(ioopm_warehouse_t *warehouse, ioopm_cart_t *cart,char *merch_name , int quant) 
{
  merch_t *merch = find_merch(warehouse, ptr_elem(merch_name));
if(total_stock(merch->location) >= quant)
{
  //kolla om item finns i cart, om det finns addera ihop quant,
  if(item_in_cart(cart, merch->name))
    {
    elem_t key = ptr_elem(merch->name);
    elem_t value = ptr_elem(NULL);

    ioopm_hash_table_lookup(cart->cart_ht, key, &value);
    value.i = value.i + quant;
    ioopm_hash_table_insert(cart->cart_ht, key, value);
    }
  else //om den inte finns lägg till den
    {
    elem_t key = ptr_elem(merch->name);
    elem_t value = int_elem(quant);
    ioopm_hash_table_insert(cart->cart_ht, key, value);
    }
  }
}

void ioopm_remove_item_from_cart(ioopm_cart_t *cart, char *name)
{
  if(item_in_cart(cart, name))
  {
    elem_t key = ptr_elem(name);
    elem_t value = ptr_elem(NULL);

    ioopm_hash_table_remove(cart->cart_ht, key, &value);
  }
}

int ioopm_calculate_price(ioopm_warehouse_t *warehouse, ioopm_cart_t *cart)
{
  char **items_in_cart = cart_list(cart);
  int total_cost = 0;
  for (size_t i = 0; i < ioopm_hash_table_size(cart->cart_ht); i++)
  {
    elem_t item_in_warehouse = ptr_elem(items_in_cart[i]); // hitta pris för varan
    elem_t merch = ptr_elem(NULL);
    ioopm_hash_table_lookup(warehouse->items, item_in_warehouse, &merch);
    merch_t *item = merch.p;
    int price_merch = item->price;

    elem_t item_cart = ptr_elem(items_in_cart[i]); // hitta antalet varor
    elem_t quant = ptr_elem(NULL);
    ioopm_hash_table_lookup(cart->cart_ht, item_cart, &quant);
    int quant_in_cart = quant.i;
    total_cost = total_cost + (price_merch * quant_in_cart);
  }
  free(items_in_cart);
  return total_cost;
}

ioopm_list_t *find_shelf(ioopm_warehouse_t *warehouse, char *items_in_cart)
{
  elem_t item_in_warehouse = ptr_elem(items_in_cart); //hitta varan
  elem_t merch = ptr_elem(NULL);
  ioopm_hash_table_lookup(warehouse->items, item_in_warehouse, &merch);

  merch_t *item = merch.p;
  ioopm_list_t *location = item->location;

  return location;
}


int remove_quant_from_shelf(shelf_t *shelf, int quant)
{
   if (quant > shelf->quantity.i)
   {
    quant = quant - shelf->quantity.i;
    shelf->quantity = int_elem(0);
    return quant;
   }
   shelf->quantity = int_elem(shelf->quantity.i - quant);
   return 0;
}

int find_cart_index(ioopm_cart_list_t *cart_list, ioopm_cart_t *cart)
{
  int acc = 0;
  ioopm_cart_t *cart_temp = ioopm_linked_list_get(cart_list->all_carts, acc).p;
  while(cart->cart_int != cart_temp->cart_int)
  {
    cart = ioopm_linked_list_get(cart_list->all_carts, acc).p;
    acc++;
  }
  return acc;
}

int ioopm_checkout(ioopm_warehouse_t *warehouse, ioopm_cart_t *cart, ioopm_cart_list_t *carts)
{
  int total_price = ioopm_calculate_price(warehouse, cart);
  char **items_in_cart = cart_list(cart);

  for (int i = 0; i < ioopm_hash_table_size(cart->cart_ht); i++)
  {
    elem_t item_cart = ptr_elem(items_in_cart[i]); // hitta antalet varor
    elem_t quant = ptr_elem(NULL);
    ioopm_hash_table_lookup(cart->cart_ht, item_cart, &quant);
    int quant_in_cart = quant.i;

    int quantaux = quant_in_cart;
    ioopm_list_t *location = find_shelf(warehouse, items_in_cart[i]); // hitta shelves för varan
    link_t *shelf_curent = location->first;
    while (quantaux != 0 || shelf_curent != NULL)
    {
      shelf_t *shelf = shelf_curent->element.p;
      int remaining = remove_quant_from_shelf(shelf, quantaux);
      quantaux = remaining;
      shelf_curent = shelf_curent->next;
    }
  }
  int index = find_cart_index(carts, cart);
  ioopm_remove_cart(cart);
  ioopm_linked_list_remove(carts->all_carts, index);
  free(items_in_cart);
  return total_price;
}

int total_quant_in_all_carts(ioopm_cart_list_t *carts, char *name_item)
{
  int tot_quant = 0;
  link_t *current = carts->all_carts->first;
  while (current!= NULL)
  {
    ioopm_cart_t *current_cart = current->element.p;
    if (ioopm_hash_table_has_key_string(current_cart->cart_ht, ptr_elem(name_item)))
    {
      elem_t amount = ptr_elem(NULL);
      ioopm_hash_table_lookup(current_cart->cart_ht, ptr_elem(name_item), &amount);
      tot_quant += amount.i; 
    }
    current = current->next;
  }
  return tot_quant;
}