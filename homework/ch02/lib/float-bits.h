/*
 * float-bits.h
 */

/* Access bit-level representation floating-point number */
typedef unsigned float_bits;

/* Iterate over all 2^32 values of floats and test each value with func */
void test_all_floats(void (*func)(float));
