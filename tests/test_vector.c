#include "vector.h"

#include <stdio.h>

int main() {
    Vector v;

    vector_init(&v);

    printf("=== Push Test ===\n");

    for (int i = 0; i < 10; i++) {
        if (!vector_push_back(&v, i * 10)) {
            printf("push_back failed\n");
            return 1;
        }

        printf(
            "push=%d size=%zu capacity=%zu data=%p\n",
            i * 10,
            vector_size(&v),
            vector_capacity(&v),
            (void *)v.data
        );
    }

    printf("\n=== Get Test ===\n");

    for (size_t i = 0; i < vector_size(&v); i++) {
        printf(
            "index=%zu value=%d\n",
            i,
            vector_get(&v, i)
        );
    }

    printf("\n=== Pop Test ===\n");

    while (vector_size(&v) > 0) {
        int value = vector_pop_back(&v);

        printf(
            "pop=%d size=%zu capacity=%zu\n",
            value,
            vector_size(&v),
            vector_capacity(&v)
        );
    }

    vector_destroy(&v);

    printf("\nVector destroyed successfully\n");

    return 0;
}