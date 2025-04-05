#include "circular_array_queue.h"

#define IMPLEMENT_circular_array_queue(TYPE, SIZE) \
    CircularQueue_##TYPE* circular_queue_##TYPE##_create(void) { \
        CircularQueue_##TYPE* queue = (CircularQueue_##TYPE*)malloc(sizeof(CircularQueue_##TYPE)); \
        if (queue == NULL) { \
            return NULL; \
        } \
        queue->head = 0; \
        queue->tail = 0; \
        queue->size = SIZE; \
        return queue; \
    } \
    \
    void circular_queue_##TYPE##_destroy(CircularQueue_##TYPE* queue) { \
        if (queue != NULL) { \
            free(queue); \
        } \
    } \
    \
    bool circular_queue_##TYPE##_insert(CircularQueue_##TYPE* queue, TYPE data) { \
        if (queue == NULL || circular_queue_##TYPE##_is_full(queue)) { \
            return false; \
        } \
        queue->data[queue->tail] = data; \
        queue->tail = CIRCULAR_QUEUE_INCREMENT(queue->tail, queue->size); \
        return true; \
    } \
    \
    bool circular_queue_##TYPE##_remove(CircularQueue_##TYPE* queue, TYPE* out) { \
        if (queue == NULL || circular_queue_##TYPE##_is_empty(queue)) { \
            return false; \
        } \
        if (out != NULL) { \
            *out = queue->data[queue->head]; \
        } \
        queue->head = CIRCULAR_QUEUE_INCREMENT(queue->head, queue->size); \
        return true; \
    } \
    \
    size_t circular_queue_##TYPE##_size(const CircularQueue_##TYPE* queue) { \
        if (queue == NULL) { \
            return 0; \
        } \
        return CIRCULAR_QUEUE_SIZE(queue->head, queue->tail, queue->size); \
    } \
    \
    bool circular_queue_##TYPE##_is_empty(const CircularQueue_##TYPE* queue) { \
        if (queue == NULL) { \
            return true; \
        } \
        return CIRCULAR_QUEUE_IS_EMPTY(queue->head, queue->tail); \
    } \
    \
    bool circular_queue_##TYPE##_is_full(const CircularQueue_##TYPE* queue) { \
        if (queue == NULL) { \
            return false; \
        } \
        return CIRCULAR_QUEUE_IS_FULL(queue->head, queue->tail, queue->size); \
    } \
    \
    void circular_queue_##TYPE##_print(const CircularQueue_##TYPE* queue, void (*print_fn)(TYPE)) { \
        if (queue == NULL || print_fn == NULL) { \
            return; \
        } \
        size_t current = queue->head; \
        size_t count = circular_queue_##TYPE##_size(queue); \
        for (size_t i = 0; i < count; i++) { \
            print_fn(queue->data[current]); \
            if(i < count - 1) printf(", "); \
            current = CIRCULAR_QUEUE_INCREMENT(current, queue->size); \
        } \
        printf("\n"); \
    }