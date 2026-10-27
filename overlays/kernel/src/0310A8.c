/* KERNEL.XFF @ 0x0310A8 (20 B) - sqrtf
 * Shape `tail-call` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: frame whose only work is a single tail `j`.
 */
void sqrtf(void) {
    __ieee754_sqrtf();
}
