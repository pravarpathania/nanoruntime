#include "ring_buffer.h"

#include <assert.h>
#include <stdlib.h>

bool ringbuffer_init(ringbuffer_t *rb, size_t capacity) {
    if (capacity == 0) {
        return false;
    }

    size_t actual_capacity = capacity + 1; // We need one extra slot to differentiate between full and empty states

    rb->data = (int *)malloc(actual_capacity * sizeof(int)); 

    if (rb->data == NULL) { // Memory allocation failed
        return false;
    }

    rb->head = 0; // Start with head at 0
    rb->tail = 0; // Start with tail at 0
    rb->capacity = actual_capacity; // Set the capacity to the actual capacity (requested capacity + 1)
    return true;
}

void ringbuffer_destroy(ringbuffer_t *rb) {
    free(rb->data); // Free the allocated buffer memory

    rb->data = NULL; // Set data pointer to NULL for safety
    rb->head = 0; // Reset head index
    rb->tail = 0; // Reset tail index
    rb->capacity = 0; // Reset capacity
}


bool ringbuffer_is_full(const ringbuffer_t *rb) {
    if ((rb->tail +1) % rb->capacity == rb->head) { // If the next position of tail is head, the buffer is full
        return true; // Buffer is full
    }
    return false;
}
bool ringbuffer_is_empty(const ringbuffer_t *rb) {
    if (rb->head == rb->tail) { // If head and tail are the same, the buffer is empty
        return true; // Buffer is empty
    }
    return false;
}

bool ringbuffer_push(ringbuffer_t *rb, int value) {
    // first write as tail is the next position to write.
    if (ringbuffer_is_full(rb)) { // If the buffer is full, we need to move the head forward to make space for the new element
        return false; // Buffer is full, cannot add new element
    }
    rb->data[rb->tail] = value; // Add new element at the tail position
    rb->tail = (rb->tail + 1) % rb->capacity; // Move tail forward
    return true;
}


bool ringbuffer_pop(ringbuffer_t *rb, int *value) {
    if (ringbuffer_is_empty(rb)) {
        return false;
    }
    *value = rb->data[rb->head]; // Get the value at the head position
    rb->head = (rb->head + 1) % rb->capacity; // Move head forward
    return true; // Successfully popped an element
}