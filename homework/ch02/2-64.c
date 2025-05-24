#include <assert.h>
#include <stdio.h>

/* Return 1 when any odd bit of x equals 1; 0 otherwise.
Assume w=32 */
int any_odd_one(unsigned x) {
    // make a mask with alternating bits
    // single byte -> 0101 (5) or 1010 (A)
    // we need 4 bytes for w=32
    int mask = 0xAAAAAAAA;

    return x & mask;
}

int main() {
    assert(!any_odd_one(0x1));
    assert(any_odd_one(0x2));

    return 0;
}
