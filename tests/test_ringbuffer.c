#include "ring_buffer.h"

#include <stdio.h>

static void print_state(const ringbuffer_t *rb) {
    printf(
        "head=%zu tail=%zu capacity=%zu\n",
        rb->head,
        rb->tail,
        rb->capacity
    );
}

int main() {
    ringbuffer_t rb;

    if (!ringbuffer_init(&rb, 4)) { // Initialize ring buffer with capacity of 5 (usable capacity will be 4 due to the design)
        printf("ringbuffer_init failed\n");
        return 1;
    }

    printf("=== Initial State ===\n"); 
    print_state(&rb);

    printf("\n=== Push Test ===\n");

    for (int i = 1; i <= 4; i++) {
        bool ok = ringbuffer_push(&rb, i * 10);

        printf(
            "push %d -> %s\n",
            i * 10,
            ok ? "success" : "FAILED"
        );

        print_state(&rb);
    }

    printf("\n=== Extra Push (Should Fail) ===\n"); // Attempt to push when buffer is full, should fail

    bool ok = ringbuffer_push(&rb, 999); // This should fail because the buffer is full

    printf(
        "push 999 -> %s\n",
        ok ? "success" : "FAILED"
    );

    print_state(&rb);

    printf("\n=== Pop Test ===\n");

    int value;

    while (ringbuffer_pop(&rb, &value)) {
        printf("pop -> %d\n", value);

        print_state(&rb);
    }

    printf("\n=== Empty Pop Test ===\n");

    if (!ringbuffer_pop(&rb, &value)) {
        printf("pop failed correctly (buffer empty)\n");
    }

    print_state(&rb);

    printf("\n=== Wraparound Test ===\n");

    ringbuffer_push(&rb, 100);
    ringbuffer_push(&rb, 200);
    ringbuffer_push(&rb, 300);

    print_state(&rb);

    ringbuffer_pop(&rb, &value);
    printf("pop -> %d\n", value);

    ringbuffer_pop(&rb, &value);
    printf("pop -> %d\n", value);

    print_state(&rb);

    ringbuffer_push(&rb, 400);
    ringbuffer_push(&rb, 500);

    print_state(&rb);

    printf("\n=== Final Drain ===\n");

    while (ringbuffer_pop(&rb, &value)) {
        printf("pop -> %d\n", value);

        print_state(&rb);
    }

    ringbuffer_destroy(&rb);

    printf("\nRing buffer destroyed successfully\n");

    return 0;
}