#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
void *calloc(size_t nmemb, size_t size);
void *malloc(size_t size);
void *memset(void *s, int c, size_t n);
*/

// Note that we don't have to follow bit-level coding rules for this one.

// Write an implementation of calloc that performs the allocation by a call to
// malloc and sets the memory to zero via memset.
void *another_calloc(size_t nmemb, size_t size) {
    if (nmemb == 0 || size == 0) {
        return NULL;
    }

    size_t buf_size = nmemb * size;

    // a good way to check overflow
    if (buf_size / nmemb == size) {
        void *ptr = malloc(buf_size);
        if (ptr != NULL) {
            memset(ptr, nmemb, size);
        }
        return ptr;
    }

    return NULL;
}

int main() {
    void *p = another_calloc(0x1234, 1);
    assert(p != NULL);
    free(p);

    p = another_calloc(SIZE_MAX, 2);
    assert(p == NULL);
    free(p);

    return 0;
}
