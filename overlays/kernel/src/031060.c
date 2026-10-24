/* KERNEL.XFF @ 0x031060 (20 B) - atan2f
 * Shape `tail-call` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: frame whose only work is a single tail `j`.
 */
void atan2f(void) {
    __ieee754_atan2f();
}
