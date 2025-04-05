#define DOUBLE_ENDED_QUEUE_IMPLEMENTATION
#include "diqueue.h"
#include <check.h>
#include <stdlib.h>


// Función auxiliar para imprimir enteros (usada en pruebas)
void print_int(int value) {
    printf("%d ", value);
}

// Función auxiliar para comparar enteros
bool int_cmp(int a, int b) {
    return a == b;
}

/* ------------------------------------- */
/* Tests para cola doblemente enlazada (Deque_int) */
/* ------------------------------------- */

START_TEST(test_deque_create) {
    Deque_int* deque = deque_int_create();
    ck_assert_ptr_nonnull(deque);
    ck_assert_ptr_null(deque->head);
    ck_assert_ptr_null(deque->tail);
    ck_assert_uint_eq(deque->length, 0);
    deque_int_destroy(deque);
}
END_TEST

START_TEST(test_push_back_and_length) {
    Deque_int* deque = deque_int_create();
    
    ck_assert(deque_int_push_back(deque, 10));
    ck_assert_uint_eq(deque_int_length(deque), 1);
    
    ck_assert(deque_int_push_back(deque, 20));
    ck_assert_uint_eq(deque_int_length(deque), 2);
    
    deque_int_destroy(deque);
    ck_assert_ptr_null(deque);
}
END_TEST

START_TEST(test_push_front_and_get) {
    Deque_int* deque = deque_int_create();
    int value = 0;
    
    deque_int_push_back(deque, 10);
    deque_int_push_front(deque, 5);  // Inserta al frente
    deque_int_push_back(deque, 20);
    
    ck_assert(deque_int_get(deque, 0, &value));  // Debe ser 5
    ck_assert_int_eq(value, 5);
    
    deque_int_destroy(deque);
}
END_TEST

START_TEST(test_pop_front_and_pop_back) {
    Deque_int* deque = deque_int_create();
    deque_int_push_back(deque, 10);
    deque_int_push_back(deque, 20);
    deque_int_push_back(deque, 30);
    
    ck_assert(deque_int_pop_front(deque));  // Elimina 10
    ck_assert_uint_eq(deque_int_length(deque), 2);
    
    ck_assert(deque_int_pop_back(deque));   // Elimina 30
    ck_assert_uint_eq(deque_int_length(deque), 1);
    
    int value = 0;
    ck_assert(deque_int_get(deque, 0, &value)); // Debería ser 20
    ck_assert_int_eq(value, 20);
    
    deque_int_destroy(deque);
}
END_TEST

/* ------------------------------------- */
/* Suite de pruebas principal */
/* ------------------------------------- */

Suite* deque_suite(void){
    Suite* s = suite_create("Deque");
    
    TCase* tc_core = tcase_create("Core Functions");
    tcase_add_test(tc_core, test_deque_create);
    tcase_add_test(tc_core, test_push_back_and_length);
    tcase_add_test(tc_core, test_push_front_and_get);
    tcase_add_test(tc_core, test_pop_front_and_pop_back);
    
    suite_add_tcase(s, tc_core);
    return s;
}

int main(void) {
    int number_failed;
    SRunner* sr = srunner_create(deque_suite());
    
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}