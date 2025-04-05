#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define DECLARE_circular_array_queue(TYPE, SIZE) \
    typedef struct { \
        TYPE data[SIZE]; \
        size_t head; \
        size_t tail; \
        size_t size; \
    } CircularQueue_##TYPE; \
    \
    CircularQueue_##TYPE* circular_queue_##TYPE##_create(void); \
    void circular_queue_##TYPE##_destroy(CircularQueue_##TYPE* queue); \
    bool circular_queue_##TYPE##_insert(CircularQueue_##TYPE* queue, TYPE data); \
    bool circular_queue_##TYPE##_remove(CircularQueue_##TYPE* queue, TYPE* out); \
    size_t circular_queue_##TYPE##_size(const CircularQueue_##TYPE* queue); \
    bool circular_queue_##TYPE##_is_empty(const CircularQueue_##TYPE* queue); \
    bool circular_queue_##TYPE##_is_full(const CircularQueue_##TYPE* queue); \
    void circular_queue_##TYPE##_print(const CircularQueue_##TYPE* queue, void (*print_fn)(TYPE));
