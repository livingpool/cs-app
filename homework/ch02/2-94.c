#include "lib/float-bits.h"
#include <assert.h>
#include <stdio.h>

/* Compute 2*f. If f is NaN, then return f. */
float_bits float_twice(float_bits f) {
    /* Decompose bit representation into parts */
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    /* If f is NaN, +inf, or -inf */
    if (exp == 0xFF) {
        return f;
    }

    if (exp == 0) { // denormalized
        frac <<= 1;
    } else if (exp == 0xFF - 1) { // 2*f goes to inf
        exp = 0xFF;
        frac = 0;
    } else { // normalized
        exp += 1;
    }

    return (sign << 31) | (exp << 23) | frac;
}

int main() {
    return 0;
}
