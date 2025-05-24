#include <assert.h>
#include <stdio.h>

/* Declaration of data type where 4 bytes are packed
into an unsigned */
typedef unsigned packed_t;

/* Extract byte from word. Return as signed integer */
int xbyte(packed_t word, int bytenum);

/* Failed attempt at xbyte */
int xbyte_failed(packed_t word, int bytenum) {
    return (word >> (bytenum << 3)) & 0xFF;
}

/*
 * A: word is unsigned, so right shifts are logical -> sign info is lost
 * i.e., doesn't sign extend for negative values
 */

int xbyte_correct(packed_t word, int bytenum) {
    int max_bytenum = 3;
    return (int)word << ((max_bytenum - bytenum) << 3) >> (max_bytenum << 3);
}

int main() {
    assert(xbyte_correct(0x00112233, 0) == 0x33);
    assert(xbyte_correct(0x00112233, 1) == 0x22);
    assert(xbyte_correct(0x00112233, 2) == 0x11);
    assert(xbyte_correct(0x00112233, 3) == 0x00);

    assert(xbyte_correct(0xAABBCCDD, 0) == 0xFFFFFFDD);
    assert(xbyte_correct(0xAABBCCDD, 1) == 0xFFFFFFCC);
    assert(xbyte_correct(0xAABBCCDD, 2) == 0xFFFFFFBB);
    assert(xbyte_correct(0xAABBCCDD, 3) == 0xFFFFFFAA);

    return 0;
}
