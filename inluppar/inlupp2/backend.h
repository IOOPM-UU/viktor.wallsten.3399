#pragma once

typedef struct shelf shelf_t;
typedef struct merch merch_t;
typedef struct warehouse ioopm_warehouse_t;
typedef struct cart ioopm_cart_t;
typedef struct cart_list ioopm_cart_list_t;

struct merch
{
    char *name;
    char *description;
    int price;
    ioopm_list_t *location;
};

struct warehouse
{
 ioopm_hash_table_t *items;
 ioopm_hash_table_t *shelves;
};

struct shelf
{
    elem_t name;
    elem_t quantity;
};

struct cart_list
{
    ioopm_list_t *all_carts;
};


struct cart
{
    ioopm_hash_table_t *cart_ht;
    int cart_int;
    int sum;
};

void merch_clear(ioopm_warehouse_t *warehouse);

/// @brief adds a item 
/// @param warehouse merch operated upon
/// @param name name ot new item
/// @param description description of new item
/// @param price price of new item
void ioopm_merch_add(ioopm_warehouse_t *warehouse, char *name, char *description, int price);

/// @brief print all items in a warehouse
/// @param warehouse ht contaning all the items
void ioopm_merch_list_merch(ioopm_warehouse_t *warehouse);

/// @brief remove merch from a warehouse, including stock
/// @param warehouse warehouse to be oerated upon
/// @param name_of_merch merch to be removed
void ioopm_remove_merch(ioopm_warehouse_t *warehouse, int index);

/// @brief edit the contents of a merch
/// @param warehouse warehouse where the merch is located
/// @param name new name
/// @param description new description
/// @param price new price
void ioopm_edit_merch(ioopm_warehouse_t *warehouse, char *merch_name, char *name, char *description, int price);

/// @brief print the storage locations for a particular item
/// @param merch the merch to be printed
void ioopm_show_stock(ioopm_warehouse_t *warehouse, int index);

/// @brief destroys warehouse
/// @param warehouse the warehouse to destroy
void ioopm_warehouse_destroy(ioopm_warehouse_t *warehouse);

/// @brief edit the stock of a merch
/// @param warehouse warehouse where the merch i located
/// @param name name of merch you want to edit stock for
/// @param shelf_name a shelf you want to add stock to
/// @param quant the amount of stock you want to add
void ioopm_replenish_stock(ioopm_warehouse_t *warehouse, char *name_merch , char *shelf_name, int quant);

/// @brief created a warehouse
/// @param func a func to compare elem_t
/// @param hash_function your hash function
/// @return a warehouse
ioopm_warehouse_t *ioopm_warehouse_create(ioopm_eq_function func, ioopm_hash_func hash_function);

/// @brief adds stock to a given merch
/// @param warehouse warehouse where the merch is located
/// @param merch_name name of the merch
/// @param new_shelf the new shelf you want to add
/// @param quant the amount of stock you want to add
void ioopm_add_stock(ioopm_warehouse_t *warehouse,char *merch_name, char *new_shelf, int quant);

/// @brief gives a 
/// @param warehouse 
/// @return 

/// @brief finds the merch in a warehouse
/// @param warehouse the warehouse to search
/// @param name name of merch
/// @return a merch
merch_t *find_merch(ioopm_warehouse_t *warehouse, elem_t name);

/// @brief creates a shoppingcart
/// @param carts a list of all carts in existence, where the new cart will be added
/// @return a cart
ioopm_cart_t *ioopm_create_cart(ioopm_cart_list_t *carts);

/// @brief created a list of all carts
/// @return a list of carts
ioopm_cart_list_t *ioopm_cart_create_list();

/// @brief destroys a cart
/// @param carts teh cart to be destroyed
/// @param index which cart to be destroyed
void ioopm_cart_destroy(ioopm_cart_list_t *carts, int index);

/// @brief adds a merch to your cart
/// @param warehouse warehouse where the merch is located
/// @param cart the cart you want to add to
/// @param merch_name name of merch
/// @param quant amount of merch
void ioopm_add_to_cart(ioopm_warehouse_t *warehouse, ioopm_cart_t *cart,char *merch_name , int quant); 

/// @brief checks if a merch is in your cart
/// @param cart the cart to check
/// @param name the name of merch
/// @return true if the merch is in your cart
bool item_in_cart(ioopm_cart_t *cart, char *name);

/// @brief prints the content of a cart
/// @param cart the cart to print
void print_carts(ioopm_cart_t *cart);

/// @brief destroys all existing carts
/// @param carts the list of all existing carts
void cart_nuke(ioopm_cart_list_t *carts);

/// @brief removes a item from your cart
/// @param cart the cart to remove from
/// @param name name of item you want to remove
void ioopm_remove_item_from_cart(ioopm_cart_t *cart, char *name);

/// @brief calculated the price of all items in your cart
/// @param warehouse warehouse to check for the price
/// @param cart the cart contaning the amount of merch
/// @return the total price for the cart
int ioopm_calculate_price(ioopm_warehouse_t *warehouse, ioopm_cart_t *cart);

/// @brief calculates the price for a cart, and removes the amount of qunatity from the shelves 
/// @param warehouse where the quantity is located
/// @param cart the cart to checkout
/// @return the total cost
int ioopm_checkout(ioopm_warehouse_t *warehouse, ioopm_cart_t *cart, ioopm_cart_list_t *carts);

/// @brief checks the total amount of stock for a merch location
/// @param location the location of all the merch's shelves
/// @return the total amount of stock
int total_stock(ioopm_list_t *location);

/// @brief calculated the total quantity of a given merch added to all the carts
/// @param carts a list of all carts
/// @param name_item name of merch
/// @return the total amount of quantity in all the carts
int total_quant_in_all_carts(ioopm_cart_list_t *carts, char *name_item);

/// @brief creates a array of all the merch names in the warehouse
/// @param warehouse the warehouse operated upon
/// @return a array of keys
char **ioopm_merch_list_no_print(ioopm_warehouse_t *warehouse);

/// @brief removes a cart
/// @param cart the cart to remove
void ioopm_remove_cart(ioopm_cart_t *cart);

/// @brief lists all the carts
/// @param carts the location of all carts
void list_carts(ioopm_cart_list_t *carts);
