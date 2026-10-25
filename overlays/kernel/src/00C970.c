/* KERNEL.XFF @ 0x00C970 (60 B) - iosFloatModulo
 * Evidence: `c.eq.s y, 0` returns the 0.0f already in $f0; otherwise
 * x - y * (float)(int)(x / y) (cvt.w.s truncation, then cvt.s.w). The two
 * nops after the bc1t slot are the compiler's R5900 branch padding.
 */
float iosFloatModulo(float x, float y) {
    if (y == 0.0f) {
        return 0.0f;
    }
    return x - y * (int)(x / y);
}
