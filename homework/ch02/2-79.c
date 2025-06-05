#include <assert.h>
#include <limits.h>
#include <stdio.h>

int mul3div4(int x) {
    x = (x << 1) + x;

    int is_neg = x & INT_MIN;
    (is_neg && (x = x + (1 << 2) - 1));

    return x >> 2;
}

int main() {
    int x = 0x87654321;
    assert(mul3div4(x) == x * 3 / 4);

    return 0;
}
