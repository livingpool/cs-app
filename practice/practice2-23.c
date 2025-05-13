// extracts a value from low-order 8 bits of the argument,
// giving an integer ranging between 0 and 255.
int fun1(unsigned word) {
    return (int)((word << 24) >> 24);
}

// extracts a value from the low-order 8 bits of the argumellt,
// but it also performs sign extension.
// the result will be a number between -128 and 127.
int fun2(unsigned word) {
    return ((int)word << 24) >> 24;
}
