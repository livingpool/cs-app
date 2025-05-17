#include <assert.h>
#include <stdio.h>

// Note: we can use sizeof(int) << 3 to compute word size.
// bcos data type int is w bits long and sizeof(int) give # of bytes.

// A. any bit of x equals 1
int A(int x) {
    return !!x;
}

// B. any bit of x equals 0
int B(int x) {
    return ~x; // or !!~x
}
// C. any bit in lsb of x equals 1
int C(int x) {
    // shift by w-8
    int shift_val = (sizeof(int) - 1) << 3;

    int xleft = x << shift_val;

    return xleft; // or !!xleft
}

// D. any bit in msb of x equals 0
int D(int x) {
    // shift by w - 8
    int shift_val = (sizeof(int) - 1) << 3;

    // arithmetic right shift
    int xright = x >> shift_val;

    // zero all but lsb
    xright = xright & 0xff;

    // flip the bits and see if lsb contains any 1s
    return ~xright & 0xff;
}

int main() {
    int all_bit_one = ~0;
    int all_bit_zero = 0;
    int lsb_one = 0x1234ff;

    assert(A(all_bit_one));
    assert(!A(all_bit_zero));
    assert(A(lsb_one));

    assert(B(all_bit_zero));
    assert(!B(all_bit_one));
    assert(B(lsb_one));

    assert(C(all_bit_one));
    assert(!C(all_bit_zero));
    assert(C(lsb_one));

    assert(!D(all_bit_one));
    assert(D(all_bit_zero));
    assert(D(lsb_one));

    return 0;
}
