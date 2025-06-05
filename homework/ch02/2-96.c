#include "lib/float-bits.h"
#include <assert.h>
#include <stdio.h>

/*
 * Compute (int) f.
 * If conversion causes overflow or f is NaN, return 0x80000000
 *
 * For floating-point number f, this function computes (int)f. Your function should round toward zero.
 */
int float_f2i(float_bits f) {
    /* Decompose bit representation into parts */
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    unsigned bias = (1 << (8 - 1)) - 1;
    int E = exp - bias;
    int res;

    /*
     * Largest exponent: 11111110
     * -> E = (2^8 - 2) - (2^7 - 1) = 2^7 - 1
     * -> largest float: (2 - 2^(-23)) * 2^127
     */
    // TODO: f = 1.abc has exp all zeroes??

    if (exp >= 0 && E < 0) { // f < 1
        res = 0;
    } else if (E >= 31) { // conversion overflows
        res = 0x80000000;
    } else {
        unsigned M = frac | 0x800000; // add implicit leading 1
        if (E > 23) {
            res = M << (E - 23);
        } else { // round some bits to zero
            res = M >> (23 - E);
        }
    }

    return sign ? -res : res;
}

void test(float f) {
    int i1 = (int)f;
    int i2 = float_f2i(f);
    if (i1 != i2) {
        printf("cast: %d, f2i: %d, f: %f\n", i1, i2, f);
    }
}

int main() {
    test_all_floats(&test);
    return 0;
}
