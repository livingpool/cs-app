#include <assert.h>
#include <stdio.h>

int main() {
    int x = 0x89ABCDEF;
    int y = 0x76543210;

    int mask = 0xff;
    int res = (x & mask) | (y & ~mask);

    assert(res == 0x765432EF);

    return 0;
}
