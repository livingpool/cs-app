#include <assert.h>
#include <stdio.h>

/*
 * Assume a w-bit data type.
 */

// A.
// Assume 0 <= k < w
int A(int k) {
    return ~0 << k;
}

// B.
// Assume 0 <= j,k < w
int B(int j, int k) {
    return ~(~0 << k) << j;
}

int main() {
    assert(A(8) == 0xFFFFFF00);
    assert(B(8, 16) == 0x00FFFF00);

    return 0;
}
