#include <assert.h>
#include <math.h>
#include <stdio.h>

/*
 * You have been assigned the task of writing a C function to
 * compute a floating-point representation of 2^x.
 */

// 32-bit: k = 8, n = 23

float u2f(unsigned x) {
    return *(float *)&x;
}

float fpwr2(int x) {
    /* Result exponent and fraction */
    unsigned exp, frac;
    unsigned u;
    if (x < 2 - pow(2, 7) - 23) {
        /* Too small. Return 0.0 */
        // Very close to 0, so it's denormalized.
        // E = 1 - bias = 2 -2^(k-1) = 2 - 2^7
        // target M = 2^(-23) -> not representable
        // -> V = M * 2^E; x = log2(V) = -23 + 2 - 2^7
        exp = 0;
        frac = 0;
    } else if (x < 2 - pow(2, 7)) {
        /* Denormalized result */
        // Denormalized: 0 <= 2^x < 1
        // E = 2 - 2^7
        // calc M = f from V = M * 2^E
        exp = 0;
        frac = 1 << (unsigned)(x - (2 - pow(2, 7) - 23));
    } else if (x < pow(2, 7) - 1 + 1) {
        /* Normalized result. */
        // max e = 11...10
        // E = max e - bias = (2^8 - 2) - (2^7 - 1) = 2^7 - 1
        exp = pow(2, 7) - 1 + x;
        frac = 0;
    } else {
        /* Too big. Return +inf */
        exp = 0xFF;
        frac = 0;
    }

    /* Pack exp and frac into 32 bits */
    u = exp << 23 | frac;
    /* Return as float */
    return u2f(u);
}

int main() {
    assert(fpwr2(0) == powf(2, 0));
    assert(fpwr2(100) == powf(2, 100));
    assert(fpwr2(-100) == powf(2, -100));
    assert(fpwr2(10000) == powf(2, 10000));
    assert(fpwr2(-10000) == powf(2, -10000));

    return 0;
}
