#ifndef RING_BUFFER_H // Include guard to prevent multiple inclusions
#define RING_BUFFER_H

#include <stddef.h> // For size_t
#include <stdbool.h> // For bool type

typedef struct{
    int *data; // Pointer to the array that holds the elements of the ring buffer 
    size_t head; // Index of the head of the buffer (the position where the next element will be added)
    size_t tail; // Index of the tail of the buffer (the position of the oldest element in the buffer)
    size_t capacity; // Usable capacity + 1. The actual number of elements that can be stored in the buffer is capacity - 1, because one slot is used to differentiate between full and empty states.
} ringbuffer_t;    

bool ringbuffer_init(ringbuffer_t *rb, size_t capacity); // Initializes the ring buffer by allocating memory for the buffer array and setting head and tail indices to 0.

void ringbuffer_destroy(ringbuffer_t *rb); // Frees the memory allocated for the buffer array and resets head, tail, and capacity to 0.         
bool ringbuffer_is_full(const ringbuffer_t *rb); // Checks if the ring buffer is full by comparing the head and tail indices.
bool ringbuffer_is_empty(const ringbuffer_t *rb);
bool ringbuffer_push(ringbuffer_t *rb, int value); // Adds an element to the end of the ring buffer. If the buffer is full, it should overwrite the oldest element (the one at the tail) and move the tail index forward.
bool ringbuffer_pop(ringbuffer_t *rb, int *value); // Removes an element from the front of the ring buffer (the one at the head) and stores it in the provided value pointer. If the buffer is empty, it should return false.
#endif