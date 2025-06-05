#include "lib/random.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>

/* Create some arbitrary values */
/*
int x = random();
int y = random();
*/

/* Convert to unsigned */
/*
unsigned ux = (unsigned)x;
unsigned uy = (unsigned)y;
*/

/*
 * A. (x<y) == (-x>-y)
 *
 * INT_MAX = -INT_MIN - 1
 * x = INT_MIN, y = INT_MAX; -x = -INT_MIN -> undefined behavior!
 *
 * B. ((x+y)<<4) + y-x == 17*y+15*x
 *
 * 17 * y = (y << 4) + y;
 * 15 * x = (x << 4) - x;
 *
 * (x + y) << 4 can be expanded to (x << 4) + (y << 4);
 * using distributive properties of bitwise operations.
 * -> see 2.5 Summary. I am not so sure about this part,
 *  but basically we can think of it as (x + y) * 16
 *
 * C. ~x+~y+1 == ~(x+y)
 *
 * ~x + 1 + ~y + 1 - 1
 *  = (-x) + (-y) - 1
 *  = - (x + y) - 1
 *  = ~(x + y) + 1 - 1
 *  = ~(x + y)
 *
 * D. (ux-uy) == -(unsigned)(y-x)
 *
 * (ux-uy) = -(uy-ux)
 *  = -(unsigned)(y-x)
 *
 * E. ((x >> 2) << 2) <= x
 *
 * ((x >> 2) << 2) may lose some bits
 * if x > 0, lhs becomes smaller -> true
 * if x < 0, lhs also becomes smaller -> true
 *
 * ((x >> 2) << 2)
 *  = x & ~0x3
 *
 */

int A(int x, int y) {
    printf("%d", -x); // this prints INT_MIN on my machine
    return (x < y) == (-x > -y);
}

int B(int x, int y) {
    return ((x + y) << 4) + y - x == 17 * y + 15 * x;
}

int C(int x, int y) {
    return ~x + ~y + 1 == ~(x + y);
}

int D(int x, int y) {
    unsigned ux = (unsigned)x;
    unsigned uy = (unsigned)y;

    return (ux - uy) == -(unsigned)(y - x);
}

int E(int x, int y) {
    return ((x >> 2) << 2) <= x;
}

// gcc homework/ch02/2-82.c homework/ch02/lib/random.c -o main && ./main

int main() {
    init_seed();
    int x = random_int();
    int y = random_int();

    assert(!A(INT_MIN, 0));
    assert(B(x, y));
    assert(C(x, y));
    assert(D(x, y));
    assert(E(x, y));

    return 0;
}
