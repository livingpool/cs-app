/*
 * show-bytes.c
 * refer to section 2.1.3 for an explanation of the code
 *
 * We use typedef to define data type byte_pointer as a pointer to an object
 * of type unsigned char. Such a byte pointer references a sequence of bytes
 * where each byte is considered to be a nonnegative integer.
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

void show_int(int x) {
    show_bytes((byte_pointer)&x, sizeof(int));
}

void show_float(float x) {
    show_bytes((byte_pointer)&x, sizeof(float));
}

void show_pointer(void *x) {
    show_bytes((byte_pointer)&x, sizeof(void *));
}

void test_show_bytes(int val) {
    int ival = val;
    float fval = (float)ival;
    int *pval = &ival;

    show_int(ival);
    show_float(fval);
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
 * 48 01 00 00
 * 00 00 a4 43
 * 18 ea 3f 6b 01 00 00 00
 * -> little endian
 *
 * Linux64
 *
 * output:
 * 48 01 00 00
 * 00 00 a4 43
 * a8 1e 71 ee fc 7f 00 00
 * -> little endian
 */
