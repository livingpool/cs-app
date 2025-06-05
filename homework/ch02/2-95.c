#include "lib/float-bits.h"
#include <assert.h>
#include <stdio.h>

/* Compute 0.5*f. If f is NaN, then return f. */
float_bits float_half(float_bits f) {
    /* Decompose bit representation into parts */
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    /* If f is NaN, +inf, or -inf */
    if (exp == 0xFF) {
        return f;
    }

    /*
     * Rounding is involved!
     * For round-to-even mode, we just care about the last two bits of frac.
     * 00 -> 0: just >> 1
     * 01 -> 0: (round to even) just >> 1
     * 10 -> 1: just >> 1
     * 11 -> 0: (round to even) >> 1 and then + 1
     */
    int rounding_addition = (exp & 0x3) == 0x3;

    if (exp == 0) { // denormalized
        exp >>= 1;
        exp += rounding_addition;
    } else if (exp == 1) { // normalized to denormalized
        // The idea is that we can treat the last bit of exp as the implicit leading 1
        // for normalized f.
        // For exp == 1, E = 1-bias == E for denormalized.
        // So, this is equivalent to just operating on M, i.e., M >> 1 (and rounding).
        int rest = f & 0x7FFFFFFF;
        rest >>= 1;
        rest += rounding_addition;

        exp = 0; // exp = rest >> 23 & 0xFF gives the same result
        frac = rest & 0x7FFFFF;
    } else { // normalized
        exp -= 1;
    }

    return (sign << 31) | (exp << 23) | frac;
}

int main() {
    return 0;
}
