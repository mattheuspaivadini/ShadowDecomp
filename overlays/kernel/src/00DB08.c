/* KERNEL.XFF @ 0x00DB08 (20 B) - iosPowf
 * Shape `tail-call` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: frame whose only work is a single tail `j`.
 */
void iosPowf(void) {
    powf();
}
