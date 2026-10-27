/* KERNEL.XFF @ 0x031030 (20 B) - acosf
 * Shape `tail-call` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: frame whose only work is a single tail `j`.
 */
void acosf(void) {
    __ieee754_acosf();
}
