#include <assert.h>
#include <limits.h>
#include <stdio.h>

/* Divide by power of 2. Assume 0 <= k < w-1 */
int divide_power2(int x, int k) {
    // return x / 2^k
    // correct rounding: integer division rounds towards zero.
    // see section 2.3.7: Dividing by Powers of 2
    // for 2's complement division by a power of 2.
    int is_neg = x & INT_MIN;
    (is_neg && (x = x + (1 << k) - 1));
    return x >> k;
}

int main() {
    int x = 0x80000007;
    assert(divide_power2(x, 1) == x / 2);
    assert(divide_power2(x, 2) == x / 4);

    return 0;
}
