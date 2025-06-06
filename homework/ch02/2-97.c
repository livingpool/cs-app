#include "lib/float-bits.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>

/* Assume i > 0, calculate i's bit length */
int bits_length(int i) {
    if ((i & INT_MIN) != 0) { // i < 0
        return 32;
    }

    unsigned u = (unsigned)i;
    int length = 0;
    while (u >= (1 << length)) {
        length++;
    }

    return length;
}

/* Generate bit mask of length l
 * 00...0(32-l) 11...1(l)
 *
 * e.g.
 * 3  => 0x00000007
 * 16 => 0x0000FFFF
 */
unsigned bits_mask(int l) {
    return (unsigned)-1 >> (32 - l);
}

/* Compute (float) i */
float_bits float_i2f(int i) {
    unsigned sign, exp, frac;
    unsigned rest;     // bits that are to be placed in frac (implicit leading 1 stripped)
    unsigned exp_sign; // float representation of i without the sign bit
    unsigned bits_len;
    unsigned E;
    unsigned bias = 0x7F;

    if (i == 0) {
        sign = 0;
        exp = 0;
        frac = 0;
        return sign << 31 | exp << 23 | frac;
    }

    if (i == INT_MIN) { // this is to avoid negating INT_MIN later
        sign = 1;
        exp = bias + 31;
        frac = 0;
        return sign << 31 | exp << 23 | frac;
    }

    sign = 0;
    if (i < 0) {
        sign = 1;
        i = -i;
    }

    bits_len = bits_length(i);
    E = bits_len - 1;
    exp = bias + E;

    rest = i & bits_mask(E);

    if (E <= 23) { // no rounding required
        frac = rest << (23 - E);
        exp_sign = exp << 23 | frac;
    } else { // round to even
        /*
         * Practice 2.50 (round to even):
         *
         * 10.010 -> 10.0
         * 10.011 -> 10.0
         * 10.110 -> 11.0
         * 11.001 -> 11.0
         *
         * Note that 11.10 -> 100.0 bcos 11 is odd (giving the else case below)
         */

        int offset = E - 23;
        int rounding_mid = 1 << (offset - 1);

        unsigned rounded_part = rest & bits_mask(offset);
        frac = rest >> offset;
        exp_sign = exp << 23 | frac;

        if (rounded_part < rounding_mid) {
        } else if (rounded_part > rounding_mid) {
            exp_sign += 1;
        } else {
            if ((frac & 0x1) == 1) {
                exp_sign += 1;
            }
        }
    }

    return sign << 31 | exp_sign;
}

int main() {
    for (int i = INT_MIN; i <= INT_MAX; i++) {
        float_bits bits = float_i2f(i);
        float f = *(float *)&bits;

        if (f == (float)i) {
            continue;
        } else {
            printf("incorrect! f=%f, i=%x\n", f, i);
            break;
        }
    }

    return 0;
}
