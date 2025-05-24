#include <string.h>

/* Copy integer into buffer if space is available */
/* WARNING: The following code is buggy */
void copy_int(int val, void *buf, int maxbytes) {
    if (maxbytes - sizeof(val) >= 0)
        memcpy(buf, (void *)&val, sizeof(val));
}

/*
 * A: the sizeof operator returns a value of type size_t, which is unsigned.
 * So maxbytes is first converted to unsigned before the subtraction.
 * unsigned subtraction >= 0.
 *
 * B: if (maxbytes >= (int)sizeof(val))
 */
