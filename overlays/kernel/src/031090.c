/* KERNEL.XFF @ 0x031090 (20 B) - powf
 * Shape `tail-call` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: frame whose only work is a single tail `j`.
 */
void powf(void) {
    __ieee754_powf();
}
