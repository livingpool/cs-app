#include <assert.h>
#include <stdio.h>

unsigned f2u(float x) {
    return *(unsigned *)&x;
}

/*
 * Fill in the return value for the following procedure,
 * which tests whether its first argument is less than or equal to its second.
 *
 * You can assume that neither argument is NaN.
 * The two flavors of zero, +0 and −0, are considered equal.
 */
int float_le(float x, float y) {
    unsigned ux = f2u(x);
    unsigned uy = f2u(y);

    /* Get the sign bits */
    unsigned sx = ux >> 31;
    unsigned sy = uy >> 31;

    /* Give an expression using only ux, uy, sx, and sy */
    return (ux << 1 == 0 && uy << 1 == 0) || /* both zeros (infinities) */
           (sx && !sy) ||                    /* x < 0, y >= 0 or x <= 0, y > 0 */
           (!sx && !sy && ux <= uy) ||       /* x > 0, y >= 0 or x >= 0, y > 0 */
           (sx && sy && ux >= uy);           /* x < 0, y <= 0 or x <= 0, y < 0 */
}

int main() {
    assert(float_le(-0, +0));
    assert(float_le(+0, -0));
    assert(float_le(0, 3));
    assert(float_le(-4, -0));
    assert(float_le(-4, 4));

    return 0;
}
