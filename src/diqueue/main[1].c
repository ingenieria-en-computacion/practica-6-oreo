#define DOUBLE_ENDED_QUEUE_IMPLEMENTATION
#include "diqueue.h"
#include <stdio.h>

void print_int(int value) {
    printf("%d", value);
}

bool int_cmp(int a, int b) {
    return a == b;
}

void print_char(char value) {
    printf("%c", value);
}

bool char_cmp(char a, char b) {
    return a == b;
}

int main() {
    Deque_int* nums = deque_int_create();
    
    deque_int_push_back(nums, 10);
    deque_int_push_back(nums, 20);
    deque_int_push_front(nums, 5);
    
    printf("Deque de enteros: ");
    deque_int_print(nums, print_int); 
    deque_int_pop_front(nums);
    deque_int_pop_back(nums);
    
    printf("\nDeque de enteros después de eliminar: ");
    deque_int_print(nums, print_int);

    deque_int_destroy(nums);

    Deque_char* chars = deque_char_create();
    
    deque_char_push_back(chars, 'a');
    deque_char_push_back(chars, 'b');
    deque_char_push_front(chars, 'z');
    
    printf("\nDeque de caracteres: ");
    deque_char_print(chars, print_char);
    
    deque_char_pop_front(chars);
    deque_char_pop_back(chars);
    
    printf("\nDeque de caracteres después de eliminar: ");
    deque_char_print(chars, print_char);

    deque_char_destroy(chars);
    
    return 0;
}
