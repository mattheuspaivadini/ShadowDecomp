/* KERNEL.XFF @ 0x031048 (20 B) - asinf
 * Shape `tail-call` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: frame whose only work is a single tail `j`.
 */
void asinf(void) {
    __ieee754_asinf();
}
