// In general, it is better to use a library macro rather than inventing your
// own code. This cbde seems to work on a variety of machines, however. We
// assume that the valne 1e400 'overflows to infinity.

#define POS_INFINITY 1e400
#define NEG_INFINITY (-POS_INFINITY)
#define NEG_ZERO (-1.0 / POS_INFINITY)
