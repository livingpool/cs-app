/*
 * float-bits.c
 */
#include <stdint.h>
#include <string.h>

// https://stackoverflow.com/questions/54610440/iterate-though-all-possible-floating-point-values-starting-from-lowest
// https://stackoverflow.com/questions/9410/how-do-you-pass-a-function-as-a-parameter-in-c
void test_all_floats(void (*func)(float)) {
    for (uint32_t i = 0;;) {
        float f;
        memcpy(&f, &i, sizeof(f));

        (*func)(f);

        i++;
        if (i == 0)
            break;
    }
}
