#include "lib/float-bits.h"
#include <assert.h>
#include <stdio.h>

/* Compute |f|. If f is NaN, then return f. */
float_bits float_absval(float_bits f) {
    /* Decompose bit representation into parts */
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    if (exp == 0xFF && frac != 0) {
        return f;
    }

    return (exp << 23) | frac;
}

int main() {
    return 0;
}
