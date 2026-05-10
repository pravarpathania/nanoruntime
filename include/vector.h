#ifndef VECTOR_H // Include guard to prevent multiple inclusions
#define VECTOR_H 

#include <stddef.h> // For size_t
#include <stdbool.h> // For bool type

// A simple dynamic array (vector) implementation in C++
typedef struct {
    int *data; // Pointer to the array of elements  
    size_t size; // Current number of elements in the vector
    size_t capacity; // Total capacity of the vector (number of elements it can hold before resizing)
} Vector;

void vector_init(Vector *vec); // Initializes the vector by setting size to 0 and capacity to an initial value (e.g., 4) and allocating memory for the data array.

void vector_destroy(Vector *vec); // Frees the memory allocated for the data array and resets size and capacity to 0.
  
bool vector_push_back(Vector *vec, int value); // Adds an element to the end of the vector. If the vector is at capacity, it should resize (e.g., double the capacity) before adding the new element. Returns true on success, false on failure (e.g., memory allocation failure).

int vector_pop_back(Vector *vec); // Removes the last element from the vector. If the vector is empty, this function should do nothing.

int vector_get(Vector *vec, size_t index); // Returns the element at the specified index. If the index is out of bounds, this function should handle it (e.g., return a default value or print an error message).

size_t vector_size(const Vector *vec); // Returns the current number of elements in the vector.

size_t vector_capacity(const Vector *vec);  // Returns the total capacity of the vector (the number of elements it can hold before needing to resize).

#endif