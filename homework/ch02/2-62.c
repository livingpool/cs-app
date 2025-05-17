#include <stdio.h>

int int_shifts_are_arithmetic() {
    int x = ~0;
    int shift_val = sizeof(int) << 3;

    if (x >> shift_val) {
        return 1;
    } else {
        return 0;
    }
}

// one liner: return (~0 >> 1) == ~0;

int main() {
    if (int_shifts_are_arithmetic()) {
        printf("this machine uses arithmetic right shifts for int\n");
    } else {
        printf("this machine uses logical right shifts for int\n");
    }

    return 0;
}
