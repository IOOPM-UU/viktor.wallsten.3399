#include "common.h"
#include "hash_table.h"
#include "linked_list.h"
#include "backend.h"
#include "utils_m.h"
#include <ctype.h>

void free_strdup(int index_not_used, elem_t *element, void *x)
{
    if(element->p)
    {
        free(element->p);
        element->p = NULL;
    }
}

char *ioopm_find_name_on_index(ioopm_warehouse_t *warehouse, int index)
{
  char **keys = ioopm_merch_list_no_print(warehouse);

  elem_t key = ptr_elem(keys[index]);
  elem_t value = ptr_elem(NULL);
  ioopm_hash_table_lookup(warehouse->items, key, &value);
  merch_t *merch = value.p;
  free(keys);
  return merch->name;
}

int valid_cart_id(ioopm_cart_list_t *cart_list, int index)
{
    while(index < 0 || ioopm_linked_list_size(cart_list->all_carts) - 1 < index)
    {
        index = ask_question_int("Cart does not exist, try again!");
        
    }
    return index;
}


void event_loop(ioopm_warehouse_t *warehouse, ioopm_cart_list_t *cart_list, ioopm_list_t *list_to_free)
{
    char n;
    do
    {
        n = ask_question_menu("Choose:");
        n = toupper(n);
        if (n == 'A') {
                char *name = ask_question_string("Name of the item:");
                ioopm_linked_list_append(list_to_free, ptr_elem(name));
                while(ioopm_hash_table_has_key_string(warehouse->items, ptr_elem(name)))
                {
                    name = ask_question_string("Item already in warehouse, try again!");
                    ioopm_linked_list_append(list_to_free, ptr_elem(name));
                }
                char *desc = ask_question_string("Description:");
                int price = ask_question_int("Price:");
                while(price < 0)
                {
                    price = ask_question_int("Invalid price, try again!");
                }
                char *shelf = ask_question_shelf("Shelf:");
                ioopm_linked_list_append(list_to_free, ptr_elem(shelf));
                while(ioopm_hash_table_has_key_string(warehouse->shelves, ptr_elem(shelf)))
                {
                    shelf = ask_question_shelf("Shelf is occupied, try again!"); 
                    ioopm_linked_list_append(list_to_free, ptr_elem(shelf));
                }
                int quant = ask_question_int("Quantity:");
                while(quant < 0)
                {
                    quant = ask_question_int("Invalid quantity, try again!");
                }
                ioopm_merch_add(warehouse, name, desc, price);
                ioopm_add_stock(warehouse, name, shelf, quant);

                ioopm_linked_list_append(list_to_free, ptr_elem(desc));
        }
        if (n == 'L') {

            ioopm_merch_list_merch(warehouse);
            printf("\n");
        }
        if (n == 'R') {
            ioopm_merch_list_merch(warehouse);
            int index = ask_question_int("Index:");
            while(index < 0 || ioopm_hash_table_size(warehouse->items) < index || ioopm_hash_table_is_empty(warehouse->items))
            {
               index = ask_question_int("Invalid input or the warehouse is empty, try again!");
            }
            char *merch_name = ioopm_find_name_on_index(warehouse, index);
            ioopm_list_t *num_carts = cart_list->all_carts;
            for (int i = 0; i < ioopm_linked_list_size(num_carts); i++)
            {   
                ioopm_cart_t *cart = ioopm_linked_list_get(cart_list->all_carts, i).p;
                if (item_in_cart(cart, merch_name))
                {
                     
                    printf("Not allowed to edit a merch that is in a cart\n");
                    goto jump_r;
                }
            }

            ioopm_remove_merch(warehouse, index);
            jump_r:
        }
        if (n == 'E') {
            if(ioopm_hash_table_size(warehouse->items) == 0){ // om inga item finns
                printf("Empty stock, add items!\n");
                }            
            ioopm_merch_list_merch(warehouse);
            char *merch_name = ask_question_string("Enter name of item you wish to edit");
            ioopm_list_t *num_carts = cart_list->all_carts;
            for (int i = 0; i < ioopm_linked_list_size(num_carts); i++)
            {   
                ioopm_cart_t *cart = ioopm_linked_list_get(cart_list->all_carts, i).p;
                if (item_in_cart(cart, merch_name))
                {
                    printf("not allowed to edit a item that is in a cart\n");
                    goto jump;
                }
            }
            
            while(!ioopm_hash_table_has_key_string(warehouse->items, ptr_elem(merch_name)))
            {
                merch_name = ask_question_string("Item not in warehouse, try again!");
                ioopm_linked_list_append(list_to_free, ptr_elem(merch_name));
            }

            char *new_name = ask_question_string("Enter a new name for the item or the same");
            ioopm_linked_list_append(list_to_free, ptr_elem(new_name));
            while(ioopm_hash_table_lookup(warehouse->items, ptr_elem(new_name), &ptr_elem(NULL)) && strcmp(merch_name, new_name) != 0) 
            {   
                new_name = ask_question_string("Item already i warehouse, try a new one!");
                ioopm_linked_list_append(list_to_free, ptr_elem(new_name));
            }

            char *description = ask_question_string("Description");
            int price = ask_question_int("Price");
            ioopm_edit_merch(warehouse, merch_name, new_name, description, price);
            ioopm_linked_list_append(list_to_free, ptr_elem(merch_name));
            ioopm_linked_list_append(list_to_free, ptr_elem(description));
            jump:


        }
        if (n == 'S') {
            if(ioopm_hash_table_size(warehouse->items) == 0){ // om inga item finns
                printf("Empty stock, add items!\n");
            }
            else
            {
            ioopm_merch_list_merch(warehouse);
            int index = ask_question_int("Index:");
            while(index < 0 || ioopm_hash_table_size(warehouse->items) < index)
            {
                index = ask_question_int("Invalid input, try again!");
            }
            ioopm_show_stock(warehouse, index);
            printf("\n");
            }
        }
        if (n == 'P'){
            char *name = ask_question_string("Name of item:");
            ioopm_linked_list_append(list_to_free, ptr_elem(name));
            while (!ioopm_hash_table_lookup(warehouse->items, ptr_elem(name), &ptr_elem(NULL)))
            {
                name = ask_question_string("Item not in warehouse\n");
                ioopm_linked_list_append(list_to_free, ptr_elem(name));
            }
            
            int quant = ask_question_int("Quantity:");
            char *shelf_name = ask_question_shelf("Shelf name:");
            ioopm_replenish_stock(warehouse, name, shelf_name, quant);
            
            ioopm_linked_list_append(list_to_free, ptr_elem(shelf_name));
        
        }
        if (n == 'C'){ //create cart

            ioopm_cart_t *cart = ioopm_create_cart(cart_list);
            printf("Cart %d created! \n", cart->cart_int);
            printf("\n");

        }
        if (n == 'M'){ //remove cart
            if(ioopm_linked_list_size(cart_list->all_carts) == 0)
            {
                printf("No carts to remove! \n");
            }
            else{
                list_carts(cart_list);
                int index = ask_question_int("Cart index:");
                index = valid_cart_id(cart_list, index);

                ioopm_cart_destroy(cart_list, index);
                printf("Cart %d removed \n", index);
                printf("\n");
                
            }
        }
        if (n == 'T'){ //add to cart
            list_carts(cart_list);
            int cart_id = ask_question_int("Cart index:");
            cart_id = valid_cart_id(cart_list, cart_id);
            ioopm_merch_list_merch(warehouse);
            char *merch_name = ask_question_string("Name of item to add:");
            ioopm_linked_list_append(list_to_free, ptr_elem(merch_name));
            while(find_merch(warehouse, ptr_elem(merch_name)) == NULL)
            {
                merch_name = ask_question_string("Try again!");
                ioopm_linked_list_append(list_to_free, ptr_elem(merch_name));
            }
            int quant = ask_question_int("Quantity:");
            merch_t *merch = find_merch(warehouse, ptr_elem(merch_name));
            while(total_stock(merch->location) < quant || total_stock(merch->location) < (total_quant_in_all_carts(cart_list, merch_name) + quant))
            {
                printf("%d %s in stock,", total_stock(merch->location) - total_quant_in_all_carts(cart_list, merch_name), merch_name);
                quant = ask_question_int(" try again!");
            }
            ioopm_cart_t *cart = ioopm_linked_list_get(cart_list->all_carts, cart_id).p;
            ioopm_add_to_cart(warehouse, cart, merch_name, quant);
            printf("%s added to cart.\n", merch_name);
            printf("Items in cart %d:\n", cart_id);
            print_carts(cart);
            printf("\n");
        }
        if (n == 'V'){ // remove from cart
            list_carts(cart_list);
            int cart_id = ask_question_int("Cart index:");
            cart_id = valid_cart_id(cart_list, cart_id);
            ioopm_cart_t *cart = ioopm_linked_list_get(cart_list->all_carts, cart_id).p;
            print_carts(cart);
            if(ioopm_hash_table_size(cart->cart_ht) == 0)
            {
                printf("cart is empty\n");
            }
            else
            {
            
            char *merch_name = ask_question_string("Item:");
            ioopm_linked_list_append(list_to_free, ptr_elem(merch_name));
            while(!item_in_cart(cart, merch_name))
            {
                merch_name = ask_question_string("Item not in cart, try again:");
                ioopm_linked_list_append(list_to_free, ptr_elem(merch_name));
            }
            ioopm_remove_item_from_cart(cart, merch_name);
            printf("%s removed from cart %d.\n", merch_name, cart_id);
            }
        }
        if (n == 'O'){ //calculate cost
            list_carts(cart_list);
            int cart_id = ask_question_int("Cart index:");
            cart_id = valid_cart_id(cart_list,cart_id);
            ioopm_cart_t *cart = ioopm_linked_list_get(cart_list->all_carts, cart_id).p;
            int total_cost = ioopm_calculate_price(warehouse, cart);
            printf("Total cost is : %d\n", total_cost);

        }
        if(n == 'H') //checkout
        {
            list_carts(cart_list);
            int cart_id = ask_question_int("Cart index: ");
            cart_id = valid_cart_id(cart_list, cart_id);
            ioopm_cart_t *cart = ioopm_linked_list_get(cart_list->all_carts, cart_id).p;
            int total_cost = ioopm_checkout(warehouse, cart, cart_list);
            printf("Cart %d has checked out\nTotal cost is : %d\n",cart_id , total_cost);
        }
        if (n == 'N')
        {
            if(ioopm_linked_list_size(cart_list->all_carts) == 0)
            {
                printf("No cart exists\n");
            }
            else
            {
            printf("enter index of cart to print\n");
            list_carts(cart_list);
            int index = ask_question_int("cart index\n");
            index = valid_cart_id(cart_list, index);
            ioopm_cart_t *cart = ioopm_linked_list_get(cart_list->all_carts, index).p;
            print_carts(cart);
            }
        }
    }
    while(n != 'Q');
}

int main(void)
{
    ioopm_warehouse_t *warehouse = ioopm_warehouse_create(compare_str, hash_func_string);
    ioopm_cart_list_t *cart_list = ioopm_cart_create_list();
    ioopm_cart_t *cart = ioopm_create_cart(cart_list);
    ioopm_list_t *list_to_free = ioopm_linked_list_create(compare_str);

    event_loop(warehouse, cart_list, list_to_free);

    ioopm_warehouse_destroy(warehouse);
    cart_nuke(cart_list);
    ioopm_linked_list_apply_to_all(list_to_free, free_strdup, NULL);
    ioopm_linked_list_destroy(list_to_free);
    list_to_free = NULL;
}