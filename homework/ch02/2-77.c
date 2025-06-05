#include <assert.h>
#include <limits.h>
#include <stdio.h>

// To be efficient, we want to use only the operations +, -, and <<.
// For the following values of K, write C expressions to
// perform the multiplication using at most three operations per expression.

int mulA(int x) {
    return (x << 4) + x;
}

int mulB(int x) {
    return -((x << 3) - x);
}

int mulC(int x) {
    return (x << 6) - (x << 2);
}

int mulD(int x) {
    return -((x << 7) - (x << 4));
}

int main() {
    int x = 2;
    assert(mulA(x) == x * 17);
    assert(mulB(x) == x * (-7));
    assert(mulC(x) == x * 60);
    assert(mulD(x) == x * (-112));

    x = INT_MIN;
    assert(mulA(x) == x * 17);
    assert(mulB(x) == x * (-7));
    assert(mulC(x) == x * 60);
    assert(mulD(x) == x * (-112));

    x = INT_MAX;
    assert(mulA(x) == x * 17);
    assert(mulB(x) == x * (-7));
    assert(mulC(x) == x * 60);
    assert(mulD(x) == x * (-112));

    return 0;
}
