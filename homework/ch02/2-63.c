#include <assert.h>
#include <stdio.h>

/*
 * Constraints:
 * 1) 0 <= k <= w-1
 * 2) cannot use more right shifts or division
 */

/*
`s` stands for original sign bit value, 'b' stands for original binary bit.
-----------------------------------------------------------------------------------------
    [ k bits   w-k bits   ]
A = [s s ... s s b ... b b] represent the int number after arithmetic right shift.
L = [0 0 ... 0 s b ... b b] represent the int number after logical right shift.
m = [0 0 ... 0 s 0 ... 0 0] represent a special mask extracted only the sign bit.
M = [0 0 ... s 0 0 ... 0 0] represent m << 1.
-----------------------------------------------------------------------------------------
Then we have: A + M = L
-----------------------------------------------------------------------------------------
srl() -- calculate L from A and M.
sra() -- calculate A from L and M.
*/

// srl performs a logical right shift using an arithmetic right shift.
unsigned srl(unsigned x, int k) {
    /* Perform shift arithmetically */
    unsigned xsra = (int)x >> k;

    size_t w = sizeof(int) << 3;

    int mask = ~0 << (w - k);

    return xsra & ~mask;
}

// sra performs an arithmetic right shift using a logical right shift.
int sra(int x, int k) {
    /* Perform shift logically */
    int xsrl = (unsigned)x >> k;

    size_t w = sizeof(int) << 3;

    int m = 0x1 << (w - k - 1);
    int M = (m & xsrl) << 1;

    return xsrl - M;
}

int main() {
    unsigned test_unsigned = 0x12345678;
    int test_int = 0x12345678;

    assert(srl(test_unsigned, 4) == test_unsigned >> 4);
    assert(sra(test_int, 4) == test_int >> 4);

    test_unsigned = 0x87654321;
    test_int = 0x87654321;

    assert(srl(test_unsigned, 4) == test_unsigned >> 4);
    assert(sra(test_int, 4) == test_int >> 4);

    return 0;
}
