#include <assert.h>
#include <limits.h>
#include <stdio.h>

/* Addition that saturates to TMin or TMax */
int saturating_add(int x, int y) {
    int sum = x + y;
    int sign_mask = INT_MIN; // a 1 followed by 0s

    // if x > 0 and y > 0, but sum < 0, it's positive overflow
    // if x < 0 and y < 0, but sum > 0, it's negative overflow
    int pos_over = !(x & sign_mask) && !(y & sign_mask) && (sum & sign_mask);
    int neg_over = (x & sign_mask) && (y & sign_mask) && !(sum & sign_mask);

    (pos_over && (sum = INT_MAX) || neg_over && (sum = INT_MIN));

    return sum;
}

int main() {
    assert(saturating_add(0xFF, 0xFF) == 0xFF + 0xFF);
    assert(saturating_add(INT_MIN, 0x1) == INT_MIN + 1);

    assert(saturating_add(INT_MIN, -0x1) == INT_MIN);
    assert(saturating_add(INT_MAX, 0x1) == INT_MAX);

    return 0;
}
