
/*
 * Given a floating-point format with a k-bit exponent and an n-bit fraction,
 * write formulas for the exponent E, the significand M, the fraction f,
 * and the value V for the quantities that follow.
 * In addition, describe the bit representation.
 *
 * A. The number 7.0
 *
 * V = 7.0 = [111.0] = 1.11 * 2^2 = (-1)^s * M * 2^E
 *  -> E = 2 = e - bias; bias = 2^(k-1) - 1 = 127 for 32-bit -> e = 129
 *  -> M = 1.11 = 1 + f
 *
 * bits:
 * 0 10...01 110...0
 *
 * B. The largest odd integer that can be represented exactly
 *
 * odd number -> a bit in the significant that represents 2^0
 * largest value is obtained when all the bits are on, for 24-bit-significant -> 2^24 - 1
 *
 * ref: https://stackoverflow.com/questions/52267201/largest-odd-integer-that-can-be-represented-as-a-float
 *
 * V = 2^(n+1) - 1
 *
 * bits:
 * 0 (bias + n) 1111...1
 *
 * C. The reciprocal of the smallest positive normalized value
 *
 * smallest positive normalized value -> 0 0...1 0...0; E = 1 - bias; V = 2^(1-bias)
 *
 * reciprocal -> V = 2^(bias-1); E = bias - 1 = e - bias; e = 2^k - 2 = (2^k - 1) - 1
 *
 * bits:
 * 0 11...101 00...0
 *
 */
