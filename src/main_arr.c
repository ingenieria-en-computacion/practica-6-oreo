#include "circular_array_queue.h"

void print_int(int x) {
    printf("%d", x);
}

#define SIZE 5  // Define el tamaño de la cola
DECLARE_circular_array_queue(int, SIZE)

int main() {
    CircularQueue_int* queue = circular_queue_int_create();

    // Insertamos elementos en la cola
    circular_queue_int_insert(queue, 1);
    circular_queue_int_insert(queue, 2);
    circular_queue_int_insert(queue, 3);
    circular_queue_int_insert(queue, 4);
    circular_queue_int_insert(queue, 5);
    
    circular_queue_int_print(queue, print_int);  // Imprimimos la cola
    
    int out;
    circular_queue_int_remove(queue, &out);
    printf("\nRemoved: %d\n", out);
    
    circular_queue_int_print(queue, print_int);  // Imprimimos después de eliminar un elemento

    circular_queue_int_destroy(queue);

    return 0;
}
