/* KERNEL.XFF @ 0x031078 (20 B) - fmodf
 * Shape `tail-call` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: frame whose only work is a single tail `j`.
 */
void fmodf(void) {
    __ieee754_fmodf();
}
