#include <assert.h>
#include <limits.h>
#include <stdio.h>

/* Determine whether arguments can be subtracted without overflow */
int tsub_ok(int x, int y) {
    int res = x - y;
    int sign_mask = INT_MIN;

    // if x > 0 and y < 0, but res < 0, it's positive overflow
    // if x < 0 and y > 0, but res > 0, it's negative overflow
    int pos_over = !(x & sign_mask) && (y & sign_mask) && (res & sign_mask);
    int neg_over = (x & sign_mask) && !(y & sign_mask) && !(res & sign_mask);

    return !pos_over && !neg_over;
}

int main() {
    assert(tsub_ok(0x1234, 0x1234));
    assert(tsub_ok(INT_MAX, 0x1));
    assert(tsub_ok(INT_MIN, -0x1));

    assert(!tsub_ok(0, INT_MIN)); // INT_MAX = -INT_MIN -1 e.g. -128 ~ 127 for 8-bit
    assert(!tsub_ok(INT_MAX, -0x1));
    assert(!tsub_ok(INT_MIN, 0x1));

    return 0;
}
