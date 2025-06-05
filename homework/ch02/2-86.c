
/*
 * bias = 2^(k-1) - 1 = 2^(15-1) - 1
 *
 *                                      binary                  decimal
 * smallest positive denormalized   0 0...0(15) 0 0...0(62)1    2^(1-bias) * 2^(-63)
 * smallest positive normalized     0 0...0(14)1 1 0...0(63)    2^(1-bias) * 1
 * largest normalized               0 1...1(14)0 1 1...1(63)    2^bias * (2 - 2^63)
 */
