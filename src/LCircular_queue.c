#include "circular_queue.h"

// ---------- Implementación para int ----------

Node_int* node_int__create(int data) {
    Node_int* new_node = malloc(sizeof(Node_int));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

Node_int* node_int_destroy(Node_int* node) {
    if (node->next == NULL) {
        free(node);
        return NULL;
    }
    return node;
}

List_int* list_int_create(void) {
    List_int* list = malloc(sizeof(List_int));
    if (!list) return NULL;
    list->head = list->tail = NULL;
    list->length = 0;
    return list;
}

void list_int_destroy(List_int* list) {
    if (!list) return;
    if (list->head) {
        Node_int* current = list->head;
        Node_int* next = NULL;
        do {
            next = current->next;
            free(current);
            current = next;
        } while (current != list->head);
    }
    free(list);
}

bool list_int_insert(List_int* list, int data, size_t pos) {
    if (!list || pos > list->length) return false;

    Node_int* new_node = node_int__create(data);
    if (!new_node) return false;

    if (pos == 0) {
        if (!list->head) {
            list->head = list->tail = new_node;
            new_node->next = new_node;
        } else {
            new_node->next = list->head;
            list->head = new_node;
            list->tail->next = list->head;
        }
    } else {
        Node_int* current = list->head;
        for (size_t i = 0; i < pos - 1; ++i) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
        if (pos == list->length) {
            list->tail = new_node;
        }
    }

    list->length++;
    if (list->tail) list->tail->next = list->head;
    return true;
}

bool list_int_append(List_int* list, int data) {
    return list_int_insert(list, data, list->length);
}

bool list_int_remove_at(List_int* list, size_t pos) {
    if (!list || pos >= list->length) return false;

    Node_int* to_delete = NULL;

    if (pos == 0) {
        to_delete = list->head;
        if (list->length == 1) {
            list->head = list->tail = NULL;
        } else {
            list->head = list->head->next;
            list->tail->next = list->head;
        }
    } else {
        Node_int* current = list->head;
        for (size_t i = 0; i < pos - 1; ++i) {
            current = current->next;
        }
        to_delete = current->next;
        current->next = to_delete->next;
        if (pos == list->length - 1) {
            list->tail = current;
        }
    }

    free(to_delete);
    list->length--;
    if (list->tail) list->tail->next = list->head;
    return true;
}

bool list_int_get(const List_int* list, size_t pos, int* out) {
    if (!list || !out || pos >= list->length) return false;

    Node_int* current = list->head;
    for (size_t i = 0; i < pos; ++i) {
        current = current->next;
    }

    *out = current->data;
    return true;
}

size_t list_int_length(const List_int* list) {
    return list ? list->length : 0;
}

void list_int_print(const List_int* list, void (*print_fn)(int)) {
    if (!list || !print_fn || list->length == 0) return;

    printf("[");
    Node_int* current = list->head;
    size_t count = 0;
    do {
        print_fn(current->data);
        count++;
        if (count < list->length) printf(", ");
        current = current->next;
    } while (current != list->head);
    printf("]\n");
}

bool list_int_contains(const List_int* list, int data) {
    if (!list || list->length == 0) return false;

    Node_int* current = list->head;
    do {
        if (current->data == data) return true;
        current = current->next;
    } while (current != list->head);

    return false;
}

bool list_int_remove(List_int* list, int data) {
    if (!list) return false;
    Node_int* current = list->head;
    size_t index = 0;

    do {
        if (current->data == data) {
            return list_int_remove_at(list, index);
        }
        current = current->next;
        index++;
    } while (current != list->head);

    return false;
}
