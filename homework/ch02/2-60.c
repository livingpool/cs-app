#include <assert.h>
#include <stdio.h>

unsigned replace_byte(unsigned x, int i, unsigned char b) {
    // shift amounts must be 0 ~ w-1
    if (i < 0) {
        printf("error: i is negetive\n");
        return x;
    }
    if (i > sizeof(unsigned) - 1) {
        printf("error: too big i");
        return x;
    }

    // 1 byte has 8 bits, << 3 means * 8,
    // so i << 3 shifts the mask to the right position
    unsigned mask = 0xff << (i << 3);
    unsigned pos_byte = b << (i << 3);

    return (x & ~mask) | pos_byte;
}

int main() {
    assert(replace_byte(0x12345678, 2, 0xAB) == 0x12AB5678);
    assert(replace_byte(0x12345678, 0, 0xAB) == 0x123456AB);

    return 0;
}
