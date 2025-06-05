#include "lib/random.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>

/*
 * We are running programs on a machine where values of type int have a 32-
 * bit two’s-complement representation. Values of type float use the 32-bit IEEE
 * format, and values of type double use the 64-bit IEEE format.
 */

/* Create some arbitrary values */
// int x = random();
// int y = random();
// int z = random();

/* Convert to double */
// double dx = (double)x;
// double dy = (double)y;
// double dz = (double)z;

// note that the problems all convert int to float/double,
// bcos converting backwards will lose precision.
// see https://stackoverflow.com/questions/23420783/convert-int-max-to-float-and-then-back-to-integer

// A. (float) x == (float) dx
// returns 1; casting double to float doesn't lose precision
int A(int x, double dx) {
    return (float)x == (float)dx;
}

// B. dx - dy == (double) (x-y)
// returns 0 if x is 0 and y is INT_MIN (undefined behavior);
int B(int x, double dx, int y, double dy) {
    return dx - dy == (double)(x - y);
}

// C. (dx + dy) + dz == dx + (dy + dz)
// return 1; if (dx + dy) or (dy + dz) goes to +inf / -inf, the overall result goes to +inf / -inf.
int C(double dx, double dy, double dz) {
    return (dx + dy) + dz == dx + (dy + dz);
}

// D. (dx * dy) * dz == dx * (dy * dz)
// returns 0 when the rounded values are different;
// dx = 1e308, dy = 1e-308, dz = 1e-308; dy * dz underflows to zero.
// i didnt quite understand the comments on https://dreamanddead.github.io, but i decided to move on.
int D(double dx, double dy, double dz) {
    return (dx * dy) * dz == dx * (dy * dz);
}

// E. dx / dx == dz / dz
// returns 0 if dx != 0 and dz == 0;
int E(double dx, double dz) {
    return dx / dx == dz / dz;
}

int main() {
    init_seed();

    int x = random_int();
    int y = random_int();
    int z = random_int();
    double dx = (double)x;
    double dy = (double)y;
    double dz = (double)z;

    printf("%x %x %x\n", x, y, z);

    assert(A(x, dx));
    assert(!B(0, (double)(int)0, INT_MIN, (double)(int)INT_MIN));
    assert(C(dx, dy, dz));
    /* magic number, brute force attack */
    assert(!D((double)(int)0x64e73387, (double)(int)0xd31cb264, (double)(int)0xd22f1fcd));
    assert(!E(dx, (double)(int)0));

    return 0;
}
