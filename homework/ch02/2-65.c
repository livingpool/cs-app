#include <assert.h>
#include <stdio.h>

/*
 * So this problem involves some crazy bit hacks. Explanation:
 * https://stackoverflow.com/questions/21617970/how-can-i-check-if-a-value-has-even-parity-of-bits-or-odd/21618038#21618038
 */

/* Return 1 when x contains an odd number of 1s; 0 otherwise.
Assume w=32 */
int odd_ones(unsigned x) {
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    x &= 0x1;

    return x;
}

int main() {
    assert(odd_ones(0x10101011));
    assert(!odd_ones(0x01010101));

    return 0;
}
