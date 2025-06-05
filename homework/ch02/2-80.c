#include <assert.h>
#include <limits.h>
#include <stdio.h>

/*
 * Write code for a function threefourths that, for integer argument x,
 * computes the value of 3x/4, rounded toward zero. It should not overflow.
 */

/*
 * No overflow -> divide x by 4 first, and then multiply by 3.
 *
 * My initial thought was to simply do that, but x / 4 loses information.
 *
 * rounding to zero is a little complicated.
 * every int x, equals f(first 30 bit number) plus l(last 2 bit number)
 *
 *   f = x & ~0x3
 *   l = x & 0x3
 *   x = f + l
 *   threeforths(x) = f/4*3 + l*3/4
 *
 * f doesn't care about rounding at all, we just care about rounding from l*3/4:
 *
 *   lmul3 = (l << 1) + l
 *
 * when x > 0, rounding to zero is easy
 *
 *   lmul3div4 = lmul3 >> 2
 *
 * when x < 0, rounding to zero acts like divide_power2 in 2.78
 *
 *   bias = 0x3    // (1 << 2) - 1
 *   lmul3div4 = (lmul3 + bias) >> 2
 */
int threefourths(int x) {
    int f = x & ~0x3;
    int l = x & 0x3;

    int fdiv4 = f >> 2;
    int fdiv4mul3 = (fdiv4 << 1) + fdiv4;

    int lmul3 = (l << 1) + l;
    int is_neg = x & INT_MIN;

    int bias = (1 << 2) - 1;
    (is_neg && (lmul3 = lmul3 + bias));

    int lmul3div4 = lmul3 >> 2;

    return fdiv4mul3 + lmul3div4;
}

int main() {
    assert(threefourths(8) == 6);
    assert(threefourths(9) == 6);
    assert(threefourths(10) == 7);
    assert(threefourths(11) == 8);
    assert(threefourths(12) == 9);

    assert(threefourths(-8) == -6);
    assert(threefourths(-9) == -6);
    assert(threefourths(-10) == -7);
    assert(threefourths(-11) == -8);
    assert(threefourths(-12) == -9);

    return 0;
}
