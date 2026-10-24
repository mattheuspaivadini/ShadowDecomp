/* KERNEL.XFF @ 0x031018 (20 B) - sqrt
 * Shape `tail-call` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: frame whose only work is a single tail `j`.
 */
void sqrt(void) {
    __ieee754_sqrt();
}
