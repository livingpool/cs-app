/*
 * 2-57: add short, long, double data types
 */

#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    size_t i;
    for (i = 0; i < len; i++) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

void show_short(short x) {
    show_bytes((byte_pointer)&x, sizeof(short));
}

void show_int(int x) {
    show_bytes((byte_pointer)&x, sizeof(int));
}

void show_long(long x) {
    show_bytes((byte_pointer)&x, sizeof(long));
}

void show_float(float x) {
    show_bytes((byte_pointer)&x, sizeof(float));
}

void show_double(double x) {
    show_bytes((byte_pointer)&x, sizeof(double));
}

void show_pointer(void *x) {
    show_bytes((byte_pointer)&x, sizeof(void *));
}

void test_show_bytes(int val) {
    short sval = val;
    int ival = val;
    long lval = val;
    float fval = (float)ival;
    double dval = (double)ival;
    int *pval = &ival;

    show_short(sval);
    show_int(ival);
    show_long(lval);
    show_float(fval);
    show_double(dval);
    show_pointer(pval);
}

int main(int argc, char *argv[]) {
    int test_num = 328;

    test_show_bytes(test_num);
    return 0;
}

/*
 * 328 in decimal = 0x148
 *
 * MacOS arm
 *
 * output:
 * 48 01
 * 48 01 00 00
 * 48 01 00 00 00 00 00 00
 * 00 00 a4 43
 * 00 00 00 00 00 80 74 40
 * 14 ea 75 6d 01 00 00 00
 * -> little endian
 *
 * Linux64
 *
 * output:
 * 48 01
 * 48 01 00 00
 * 48 01 00 00 00 00 00 00
 * 00 00 a4 43
 * 00 00 00 00 00 80 74 40
 * 18 b7 2e 20 fd 7f 00 00
 * -> little endian
 */
