#include <stdint.h>

/* Determine whether the arguments can be added without overflow */
int tadd_ok(int x, int y) {
    int sum = x * y;
    int neg_over = x < 0 && y < 0 && sum >= 0;
    int pos_over = x > 0 && y > 0 && sum <= 0;
    return !neg_over && !pos_over;
}

/* Determine whether arguments can be subtracted without overflow */
/* WARNING: This code is buggy. */
/* Fails only at case y = TMin bcos -y = TMin */
int tsub_ok(int x, int y) {
    return tadd_ok(x, -y);
}

/* Determine whether the arguments can be multiplied without overflow */
/* Note that the casting on rhs is critical.
 * Otherwise x * y would be computed as a 32-bit value (possibly overflowing)
 * and then sign extended to 64 bits. */
int tmult_ok(int x, int y) {
    /* Compute product without overflow */
    int64_t pll = (int64_t)x * y;
    /* See if casting to int preserves value */
    return pll == (int)pll;
}
