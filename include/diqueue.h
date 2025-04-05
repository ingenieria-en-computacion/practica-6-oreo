#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// ----------------------------
// Macro para declarar estructuras y prototipos
// ----------------------------
#define DECLARE_DOUBLE_ENDED_QUEUE(TYPE) \
    typedef struct Node_##TYPE { \
        TYPE data; \
        struct Node_##TYPE* next; \
        struct Node_##TYPE* prev; \
    } Node_##TYPE; \
    Node_##TYPE* node_##TYPE##_create(TYPE);\ \
    Node_##TYPE* node_##TYPE##_destroy(Node_##TYPE*);\ \
    \
    typedef struct { \
        Node_##TYPE* head; \
        Node_##TYPE* tail; \
        size_t length; \
    } Deque_##TYPE; \
    \
    Deque_##TYPE* deque_##TYPE##_create(void); \
    void deque_##TYPE##_destroy(Deque_##TYPE* deque); \
    bool deque_##TYPE##_push_front(Deque_##TYPE* deque, TYPE data); \
    bool deque_##TYPE##_push_back(Deque_##TYPE* deque, TYPE data); \
    bool deque_##TYPE##_pop_front(Deque_##TYPE* deque); \
    bool deque_##TYPE##_pop_back(Deque_##TYPE* deque); \
    bool deque_##TYPE##_get(const Deque_##TYPE* deque, size_t pos, TYPE* out); \
    size_t deque_##TYPE##_length(const Deque_##TYPE* deque); \
    void deque_##TYPE##_print(const Deque_##TYPE* deque, void (*print_fn)(TYPE));

// ----------------------------
// Macro para implementación
// ----------------------------
#define IMPLEMENT_DOUBLE_ENDED_QUEUE(TYPE) \
    Node_##TYPE* node_##TYPE##_create(TYPE data) { \
        Node_##TYPE* new_node = malloc(sizeof(Node_##TYPE)); \
        new_node->data = data; \
        new_node->next = NULL; \
        new_node->prev = NULL; \
        return new_node; \
    } \
    \
    Node_##TYPE* node_##TYPE##_destroy(Node_##TYPE* node) { \
        if (node) { \
            free(node); \
        } \
        return NULL; \
    } \
    \
    Deque_##TYPE* deque_##TYPE##_create(void) { \
        Deque_##TYPE* deque = malloc(sizeof(Deque_##TYPE)); \
        if (!deque) return NULL; \
        deque->head = deque->tail = NULL; \
        deque->length = 0; \
        return deque; \
    } \
    \
    void deque_##TYPE##_destroy(Deque_##TYPE* deque) { \
        if (!deque) return; \
        Node_##TYPE* current = deque->head; \
        while (current) { \
            Node_##TYPE* temp = current; \
            current = current->next; \
            free(temp); \
        } \
        free(deque); \
    } \
    \
    bool deque_##TYPE##_push_front(Deque_##TYPE* deque, TYPE data) { \
        if (!deque) return false; \
        Node_##TYPE* new_node = node_##TYPE##_create(data); \
        if (!new_node) return false; \
        \
        if (deque->head == NULL) { \
            deque->head = deque->tail = new_node; \
        } else { \
            new_node->next = deque->head; \
            deque->head->prev = new_node; \
            deque->head = new_node; \
        } \
        deque->length++; \
        return true; \
    } \
    \
    bool deque_##TYPE##_push_back(Deque_##TYPE* deque, TYPE data) { \
        if (!deque) return false; \
        Node_##TYPE* new_node = node_##TYPE##_create(data); \
        if (!new_node) return false; \
        \
        if (deque->tail == NULL) { \
            deque->head = deque->tail = new_node; \
        } else { \
            new_node->prev = deque->tail; \
            deque->tail->next = new_node; \
            deque->tail = new_node; \
        } \
        deque->length++; \
        return true; \
    } \
    \
    bool deque_##TYPE##_pop_front(Deque_##TYPE* deque) { \
        if (!deque || deque->length == 0) return false; \
        \
        Node_##TYPE* to_delete = deque->head; \
        if (deque->head == deque->tail) { \
            deque->head = deque->tail = NULL; \
        } else { \
            deque->head = deque->head->next; \
            deque->head->prev = NULL; \
        } \
        free(to_delete); \
        deque->length--; \
        return true; \
    } \
    \
    bool deque_##TYPE##_pop_back(Deque_##TYPE* deque) { \
        if (!deque || deque->length == 0) return false; \
        \
        Node_##TYPE* to_delete = deque->tail; \
        if (deque->head == deque->tail) { \
            deque->head = deque->tail = NULL; \
        } else { \
            deque->tail = deque->tail->prev; \
            deque->tail->next = NULL; \
        } \
        free(to_delete); \
        deque->length--; \
        return true; \
    } \
    \
    bool deque_##TYPE##_get(const Deque_##TYPE* deque, size_t pos, TYPE* out) { \
        if (!deque || !out || pos >= deque->length) return false; \
        \
        Node_##TYPE* current = deque->head; \
        for (size_t i = 0; i < pos; ++i) { \
            current = current->next; \
        } \
        *out = current->data; \
        return true; \
    } \
    \
    size_t deque_##TYPE##_length(const Deque_##TYPE* deque) { \
        return deque ? deque->length : 0; \
    } \
    \
    void deque_##TYPE##_print(const Deque_##TYPE* deque, void (*print_fn)(TYPE)) { \
        if (!deque || !print_fn) return; \
        \
        printf("["); \
        Node_##TYPE* current = deque->head; \
        while (current) { \
            print_fn(current->data); \
            if (current->next) printf(", "); \
            current = current->next; \
        } \
        printf("]\n"); \
    }
