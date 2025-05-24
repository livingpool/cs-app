#include <assert.h>
#include <stdio.h>

/*
 * Why does this work? Take 8-bit [a b c d e f g h].
 * 1st step gives [a b c d e f g h] | [0 a b c d e f g] = [a ab bc cd de ef fg gh]
 * 2nd step gives [a ab bc cd de ef fg gh] | [0 0 a ab bc cd de ef] = [a ab abc abcd bcde cdef defg efgh]
 * ...
 * this is a mask where all bits are one after leftmost 1.
 *
 * Now to get rid of the trailing 1s:
 * return x ^ (x >> 1);
 */

/*
 * Generate mask indicating leftmost 1 in x. Assume w=32.
 * For example, 0xFF00 -> 0x8000, and 0x6600 --> 0x4000.
 * If x = 0, then return 0.
 */
int leftmost_one(unsigned x) {
    /*
     * first, generate a mask that all bits after leftmost one are one
     * e.g. 0xFF00 -> 0xFFFF, and 0x6000 -> 0x7FFF
     * If x = 0, get 0
     */
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;

    return x ^ (x >> 1);
}

int main() {
    assert(leftmost_one(0xFF00) == 0x8000);
    assert(leftmost_one(0x6000) == 0x4000);
    assert(leftmost_one(0x0) == 0x0);
    assert(leftmost_one(0x80000000) == 0x80000000);

    return 0;
}
