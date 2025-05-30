/*
 * is-little-endian.c
 */

#include <assert.h>
#include <stdio.h>

typedef unsigned char *byte_pointer;

int is_little_endian() {
    int test_num = 0xff;
    byte_pointer byte_start = (byte_pointer)&test_num;

    if (byte_start[0] == 0xff) {
        return 1;
    }

    return 0;
}

int main() {
    assert(is_little_endian());
    return 0;
}
