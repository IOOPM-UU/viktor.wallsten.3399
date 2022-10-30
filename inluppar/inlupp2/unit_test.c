//
// Created by Matilda Sundberg on 2022-10-09.
//
#include "common.h"
#include "hash_table.h"
#include "linked_list.h"
#include "backend.h"
#include "utils_m.h"
#include <CUnit/Basic.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

void test_create_and_destroy()
{
    ioopm_warehouse_t *warehouse = ioopm_warehouse_create(compare_str, hash_func_string);
    CU_ASSERT_PTR_NOT_NULL(warehouse);
    ioopm_warehouse_destroy(warehouse);
}

void test_add_merch_stock()
{
    char *sko = strdup("sko");
    char *vit = strdup("vit");
    char *b10 = strdup("B10");
   ioopm_warehouse_t *warehouse = ioopm_warehouse_create(compare_str, hash_func_string);
   CU_ASSERT_PTR_NOT_NULL(warehouse);
   ioopm_merch_add(warehouse, sko, vit, 199);
   CU_ASSERT_EQUAL(ioopm_hash_table_size(warehouse->items), 1);
   ioopm_add_stock(warehouse, "sko", b10, 2);
   CU_ASSERT_EQUAL(ioopm_hash_table_size(warehouse->items), 1);
   CU_ASSERT_EQUAL(ioopm_hash_table_size(warehouse->shelves), 1);
   CU_ASSERT_TRUE(ioopm_hash_table_has_key_string(warehouse->shelves, ptr_elem(("B10"))));
   ioopm_warehouse_destroy(warehouse);
   free(sko);
   free(vit);
   free(b10);
}

void test_list_merch()
{
    char *sko = strdup("sko");
    char *vit = strdup("vit");
    char *b10 = strdup("B10");
    char *a10 = strdup("A10");
    char *banan = strdup("banan");
    char *gul = strdup("gul");

   ioopm_warehouse_t *warehouse = ioopm_warehouse_create(compare_str, hash_func_string);
   CU_ASSERT_PTR_NOT_NULL(warehouse);
   ioopm_merch_add(warehouse, sko, vit, 199);
   ioopm_merch_add(warehouse, banan, gul, 10);
   ioopm_add_stock(warehouse, "sko", b10, 2);
   ioopm_add_stock(warehouse, "banan", a10, 10);
   ioopm_warehouse_destroy(warehouse);
    free(sko);
    free(vit);
    free(b10);
    free(a10);
    free(banan);
    free(gul);
}

void test_remove_merch()
{
   ioopm_warehouse_t *warehouse = ioopm_warehouse_create(compare_str, hash_func_string);
   CU_ASSERT_PTR_NOT_NULL(warehouse);
    char *sko = strdup("sko");
    char *vit = strdup("vit");
    char *banan = strdup("banan");
    char *gul = strdup("gul");
    char *b10 = strdup("B10");
    char *a10 = strdup("A10");
    ioopm_merch_add(warehouse, sko, vit, 199);
    ioopm_merch_add(warehouse, banan, gul, 10);
    ioopm_add_stock(warehouse, "sko", b10, 2);
    ioopm_add_stock(warehouse, "banan", a10, 10);
   CU_ASSERT_EQUAL(ioopm_hash_table_size(warehouse->items), 2);
   CU_ASSERT_TRUE(ioopm_hash_table_has_key_string(warehouse->items, ptr_elem("sko")));
   ioopm_remove_merch(warehouse, 0);
   CU_ASSERT_FALSE(ioopm_hash_table_has_key_string(warehouse->items, ptr_elem("banan")));
   ioopm_warehouse_destroy(warehouse);
    free(a10);
    free(banan);
    free(gul);
    free(sko);
    free(vit);
    free(b10);
}

void test_edit_merch()
{
   ioopm_warehouse_t *warehouse = ioopm_warehouse_create(compare_str, hash_func_string);
    char *sko = strdup("sko");
    char *vit = strdup("vit");
    char *banan = strdup("banan");
    char *gul = strdup("gul");
    char *b10 = strdup("B10");
    char *a10 = strdup("A10");
    char *sko_copy = strdup("sko");
    char *edit_to = strdup("keps");
    char *svart = strdup("svart");

    ioopm_merch_add(warehouse, sko, vit, 199);
    ioopm_merch_add(warehouse, banan, gul, 10);
    ioopm_add_stock(warehouse, "sko", b10, 2);
    ioopm_add_stock(warehouse, "banan", a10, 10);

   ioopm_edit_merch(warehouse, sko_copy, edit_to, svart, 50);

   CU_ASSERT_FALSE(ioopm_hash_table_has_key_string(warehouse->items, ptr_elem("sko")));
   CU_ASSERT_TRUE(ioopm_hash_table_has_key_string(warehouse->items, ptr_elem("keps")));
   CU_ASSERT_TRUE(ioopm_hash_table_has_key_string(warehouse->shelves, ptr_elem("B10")));     // samma stocken, kolla
   ioopm_show_stock(warehouse, 1);
   ioopm_warehouse_destroy(warehouse);
   free(sko);
   free(vit);
   free(sko_copy);
   free(banan);
   free(gul);
   free(b10);
   free(a10);
   free(edit_to);
   free(svart);
}


void test_replenish_stock()
{
    char *sko = strdup("sko");
    char *vit = strdup("vit");
    char *banan = strdup("banan");
    char *gul = strdup("gul");
    char *b10 = strdup("B10");
    char *sko_copy = strdup("sko");

    ioopm_warehouse_t *warehouse = ioopm_warehouse_create(compare_str, hash_func_string);
    ioopm_merch_add(warehouse, sko, vit, 199);
    ioopm_merch_add(warehouse, banan, gul, 10);
    ioopm_add_stock(warehouse, "sko", b10, 2);
    ioopm_replenish_stock(warehouse, sko_copy, "B10", 78);
    CU_ASSERT_TRUE(ioopm_hash_table_has_key_string(warehouse->shelves, ptr_elem("B10")));
    ioopm_show_stock(warehouse, 1);
    ioopm_warehouse_destroy(warehouse);

    free(sko_copy);
    free(sko);
    free(vit);
    free(banan);
    free(gul);
    free(b10);
}

void cart_test_create_destroy()
{
    ioopm_cart_list_t *carts = ioopm_cart_create_list();
    ioopm_cart_t *cart = ioopm_create_cart(carts);
    ioopm_create_cart(carts);
    ioopm_create_cart(carts);
    ioopm_create_cart(carts);
    ioopm_create_cart(carts);
    ioopm_cart_destroy(carts, 4);
    ioopm_create_cart(carts);
    CU_ASSERT_PTR_NOT_NULL(cart);
    cart_nuke(carts);
}

void cart_add_test()
{
    char *sko = strdup("sko");
    char *b10 = strdup("B10");
    char *sko_copy = strdup("sko");
    ioopm_cart_list_t *carts = ioopm_cart_create_list();
    ioopm_cart_t *cart = ioopm_create_cart(carts);
    ioopm_warehouse_t *warehouse = ioopm_warehouse_create(compare_str, hash_func_string);
    ioopm_merch_add(warehouse, sko, "vit", 199);
    ioopm_add_stock(warehouse, "sko", b10, 2);
    ioopm_add_to_cart(warehouse, cart, sko_copy, 1);
    CU_ASSERT_EQUAL(total_quant_in_all_carts(carts, "sko"), 1);
    CU_ASSERT_TRUE(item_in_cart(cart, "sko"));
    print_carts(cart);
    ioopm_warehouse_destroy(warehouse);
    cart_nuke(carts);
    free(sko);
    free(b10);
    free(sko_copy);
}

void cart_remove_test()
{
    char *sko = strdup("sko");
    char *b10 = strdup("B10");
    char *sko_copy = strdup("sko");
    char *sko_copy_2 = strdup("sko");

    ioopm_cart_list_t *carts = ioopm_cart_create_list();
    ioopm_cart_t *cart = ioopm_create_cart(carts);
    ioopm_warehouse_t *warehouse = ioopm_warehouse_create(compare_str, hash_func_string);
    ioopm_merch_add(warehouse, sko, "vit", 199);
    ioopm_add_stock(warehouse, "sko", b10, 2);
    ioopm_add_to_cart(warehouse, cart, sko_copy, 12);
    CU_ASSERT_PTR_NOT_NULL(cart->cart_ht);
    ioopm_remove_item_from_cart(cart, sko_copy_2);
    CU_ASSERT_FALSE(ioopm_hash_table_lookup(cart->cart_ht, ptr_elem("sko"), &ptr_elem(NULL)));
    ioopm_warehouse_destroy(warehouse);
    cart_nuke(carts);
    free(sko_copy);
    free(sko_copy_2);
    free(sko);
    free(b10);
}

void test_cost_one_item()
{
    char *sko = strdup("sko");
    char *b10 = strdup("B10");
    char *sko_copy = strdup("sko");
    ioopm_cart_list_t *carts = ioopm_cart_create_list();
    ioopm_cart_t *cart = ioopm_create_cart(carts);
    ioopm_warehouse_t *warehouse = ioopm_warehouse_create(compare_str, hash_func_string);
    ioopm_merch_add(warehouse, sko, "vit", 199);
    ioopm_add_stock(warehouse, "sko", b10, 2);
    ioopm_add_to_cart(warehouse, cart, sko_copy, 2);
    CU_ASSERT_EQUAL(ioopm_calculate_price(warehouse, cart), 398);
    free(sko_copy);
    ioopm_warehouse_destroy(warehouse);
    cart_nuke(carts);
    free(sko);
    free(b10);
}


void test_cost_mult_items()
{
    char *sko = strdup("sko");
    char *bil = strdup("bil");
    char *banan = strdup("banan");
    char *tvattmedel = strdup("tvättmedel");
    char *pizza = strdup("pizza");
    char *milk = strdup("milk");
    char *godis = strdup("godis");
    char *vit = strdup("vit");
    char *djur = strdup("djur");
    char *frukt = strdup("frukt");
    char *gift = strdup("gift");
    char *gott = strdup("gott");
    char *vit_ = strdup("vit");
    char *socker = strdup("socker");

    char *b10 = strdup("B10");
    char *y10 = strdup("Y10");
    char *z54 = strdup("Z54");
    char *t10 = strdup("T10");
    char *u10 = strdup("U10");
    char *i10 = strdup("I10");
    char *r18 = strdup("R18");

    char *sko_ = strdup("sko");
    char *bil_ = strdup("bil");
    char *banan_ = strdup("banan");
    char *tvattmedel_ = strdup("tvättmedel");
    char *pizza_ = strdup("pizza");
    char *milk_ = strdup("milk");
    char *godis_ = strdup("godis");


    ioopm_cart_list_t *carts = ioopm_cart_create_list();
    ioopm_cart_t *cart = ioopm_create_cart(carts);
    ioopm_warehouse_t *warehouse = ioopm_warehouse_create(compare_str, hash_func_string);
    ioopm_merch_add(warehouse, sko, vit, 199);
    ioopm_merch_add(warehouse, bil, djur, 19900);
    ioopm_merch_add(warehouse, banan, frukt, 9);
    ioopm_merch_add(warehouse, tvattmedel, gift, 19);
    ioopm_merch_add(warehouse, pizza, gott, 19);
    ioopm_merch_add(warehouse, milk, vit_, 15);
    ioopm_merch_add(warehouse, godis, socker, 9);
    ioopm_add_stock(warehouse, "sko", b10, 2);
    ioopm_add_stock(warehouse, "bil", y10, 1);
    ioopm_add_stock(warehouse, "banan", z54, 45);
    ioopm_add_stock(warehouse, "tvättmedel", t10, 10);
    ioopm_add_stock(warehouse, "pizza", u10, 20);
    ioopm_add_stock(warehouse, "milk", i10, 200);
    ioopm_add_stock(warehouse, "godis", r18, 20);
    ioopm_merch_list_merch(warehouse);
    ioopm_add_to_cart(warehouse, cart, sko_, 2);
    ioopm_add_to_cart(warehouse, cart, bil_, 1);
    ioopm_add_to_cart(warehouse, cart, banan_, 30);
    ioopm_add_to_cart(warehouse, cart, tvattmedel_, 6);
    ioopm_add_to_cart(warehouse, cart, pizza_, 10);
    ioopm_add_to_cart(warehouse, cart, milk_, 20);
    ioopm_add_to_cart(warehouse, cart, godis_, 20);
    CU_ASSERT_EQUAL(ioopm_calculate_price(warehouse, cart), 21352);
    ioopm_warehouse_destroy(warehouse);
    cart_nuke(carts);

    free(sko);
    free(bil);
    free(banan);
    free(tvattmedel);
    free(pizza);
    free(milk);
    free(godis);
    free(vit);
    free(djur);
    free(frukt);
    free(gift);
    free(gott);
    free(vit_);
    free(socker);

    free(b10);
    free(y10);
    free(z54);
    free(t10);
    free(u10);
    free(i10);
    free(r18);

    free(sko_);
    free(bil_);
    free(banan_);
    free(tvattmedel_);
    free(pizza_);
    free(milk_);
    free(godis_);
}

void test_checkout()
{
    char *sko = strdup("sko");
    char *bil = strdup("bil");
    char *vit = strdup("vit");
    char *fordon = strdup("fordon");
    char *sko_ = strdup("sko");
    char *bil_ = strdup("bil");
    char *b10 = strdup("B10");
    char *y10 = strdup("Y10");

    ioopm_cart_list_t *carts = ioopm_cart_create_list();
    ioopm_cart_t *cart = ioopm_create_cart(carts);
    ioopm_warehouse_t *warehouse = ioopm_warehouse_create(compare_str, hash_func_string);

    ioopm_merch_add(warehouse, sko, vit, 199);
    ioopm_merch_add(warehouse, bil, fordon, 19900);

    ioopm_add_stock(warehouse, "sko", b10, 2);
    ioopm_add_stock(warehouse, "bil", y10, 1);

    ioopm_add_to_cart(warehouse, cart, sko_, 2);
    ioopm_add_to_cart(warehouse, cart, bil_, 1);

    int total = ioopm_checkout(warehouse, cart, carts);
    CU_ASSERT_EQUAL(total, 20298)
    ioopm_warehouse_destroy(warehouse);
    cart_nuke(carts);
    
    free(sko);
    free(bil);
    free(vit);
    free(fordon);
    free(sko_);
    free(bil_);
    free(b10);
    free(y10);
}

int init_suite(void) {
    // Change this function if you want to do something *before* you
    // run a test suite
    return 0;
}

int clean_suite(void) {
    // Change this function if you want to do something *after* you
    // run a test suite
    return 0;
}

int main() {
    // First we try to set up CUnit, and exit if we fail
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    // We then create an empty test suite and specify the name and
    // the init and cleanup functions
    CU_pSuite my_test_suite = CU_add_suite("Tests for backend", init_suite, clean_suite);
    if (my_test_suite == NULL) {
        // If the test suite could not be added, tear down CUnit and exit
        CU_cleanup_registry();
        return CU_get_error();
    }

    // This is where we add the test functions to our test suite.
    // For each call to CU_add_test we specify the test suite, the
    // name or description of the test, and the function that runs
    // the test in question. If you want to add another test, just
    // copy a line below and change the information
    if (
            (CU_add_test(my_test_suite, "Test create and destroy:", test_create_and_destroy) == NULL) ||
            (CU_add_test(my_test_suite, "Test clear merch:", test_add_merch_stock) == NULL) ||
            (CU_add_test(my_test_suite, "Test list merch", test_list_merch) == NULL) ||
            (CU_add_test(my_test_suite, "Test remove merch", test_remove_merch) == NULL) ||
            (CU_add_test(my_test_suite, "Test edit merch", test_edit_merch) == NULL) ||
            (CU_add_test(my_test_suite, "Test replenish merch", test_replenish_stock) == NULL) ||
            (CU_add_test(my_test_suite, "Test create, destroy cart", cart_test_create_destroy) == NULL) ||
            (CU_add_test(my_test_suite, "Test add to cart", cart_add_test) == NULL) ||
            (CU_add_test(my_test_suite, "Test remove from cart", cart_remove_test) == NULL) ||
            (CU_add_test(my_test_suite, "Test price of cart with one item", test_cost_one_item) == NULL) ||
            (CU_add_test(my_test_suite, "Test price of cart mult items", test_cost_mult_items) == NULL) ||
            (CU_add_test(my_test_suite, "Test add to cart", cart_add_test) == NULL) ||
            (CU_add_test(my_test_suite, "Test add to cart", test_checkout) == NULL) ||
            0
            )
    {
        // If adding any of the tests fails, we tear down CUnit and exit
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
    // Use CU_BRM_NORMAL to only print errors and a summary
    CU_basic_set_mode(CU_BRM_VERBOSE);

    // This is where the tests are actually run!
    CU_basic_run_tests();

    // Tear down CUnit before exiting
    CU_cleanup_registry();
    return CU_get_error();
}