#include "vector.h"

#include <assert.h>
#include <stdlib.h>

static bool vector_resize(Vector *vec, size_t new_capacity) {
    int *new_data = (int *)realloc(
        vec->data,
        new_capacity * sizeof(int)
    );

    if (new_data == NULL) {
        return false;
    }

    vec->data = new_data;
    vec->capacity = new_capacity;

    return true;
}

// Initialize vector with no allocation initially
void vector_init(Vector *vec) {
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
}

void vector_destroy(Vector *vec) {
    free(vec->data);

    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
}

bool vector_push_back(Vector *vec, int value) {
    // First allocation
    if (vec->capacity == 0) {
        if (!vector_resize(vec, 4)) {
            return false;
        }
    }

    // Need growth
    if (vec->size >= vec->capacity) {
        size_t new_capacity = vec->capacity * 2;

        if (!vector_resize(vec, new_capacity)) {
            return false;
        }
    }

    vec->data[vec->size] = value;
    vec->size++;

    return true;
}

int vector_pop_back(Vector *vec) {
    assert(vec->size > 0 && "Cannot pop from an empty vector");

    int data = vec->data[vec->size - 1];

    vec->size--;

    return data;
}

int vector_get(Vector *vec, size_t index) {
    assert(index < vec->size && "Index out of bounds");

    return vec->data[index];
}

size_t vector_size(const Vector *vec) {
    return vec->size;
}

size_t vector_capacity(const Vector *vec) {
    return vec->capacity;
}