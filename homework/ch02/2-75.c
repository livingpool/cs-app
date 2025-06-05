#include <assert.h>
#include <inttypes.h>
#include <stdio.h>

// given this library function
int signed_high_prod(int x, int y) {
    int64_t mul = (int64_t)x * y;
    return mul >> 32;
}

// derived using equation (2.18)
// x' * y' / 2^w = ...
unsigned unsigned_high_prod(unsigned x, unsigned y) {
    int sign_x = x >> 31;
    int sign_y = y >> 31;
    int sign_prod = signed_high_prod(x, y);

    return sign_prod + sign_x * y + sign_y * x + sign_x * sign_y * 32;
}

/* a theorically correct version to test unsigned_high_prod func */
unsigned another_unsigned_high_prod(unsigned x, unsigned y) {
    uint64_t mul = (uint64_t)x * y;
    return mul >> 32;
}

int main(int argc, char *argv[]) {
    unsigned x = 0x12345678;
    unsigned y = 0xFFFFFFFF;

    assert(another_unsigned_high_prod(x, y) == unsigned_high_prod(x, y));
    return 0;
}
