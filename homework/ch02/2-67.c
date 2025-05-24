#include <assert.h>
#include <stdio.h>

/* The following code does not run properly on some machines */
int bad_int_size_is_32() {
    /* Set most significant bit (msb) of 32-bit machine */
    int set_msb = 1 << 31;
    /* Shift past msb of 32-bit word */
    int beyond_msb = 1 << 32;

    /* set_msb is nonzero when word size >= 32
    beyond_msb is zero when word size <= 32 */
    return set_msb && !beyond_msb;
}

/*
 * A) In section 6.5.7 Bitwise shift operators of c11 standard:
 * If the value of the right operand is negative or is
 * greater than or equal to the width of the promoted left operand, the behavior it undefined.
 */

// yields 1 when run on a machine for which an int is 32 bits, and yields 0 otherwise

// B)
int int_size_is_32() {
    // set_msb is nonzero when w >= 32
    int set_msb = 1 << 31;

    // beyond_msb is zero when w <= 32
    int beyond_msb = set_msb << 1;

    return set_msb && !beyond_msb;
}

// C)
int int_size_is_32_for_16_bit() {
    // set_msb is nonzero when w >= 32
    int set_msb = 1 << 15 << 15 << 1;

    // beyond_msb is zero when w <= 32
    int beyond_msb = set_msb << 1;

    return set_msb && !beyond_msb;
}

int main() {
    assert(int_size_is_32());
    assert(int_size_is_32_for_16_bit());

    return 0;
}
