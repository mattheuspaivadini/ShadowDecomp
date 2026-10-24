/* KERNEL.XFF @ 0x00D368 (20 B) - iosFmodf
 * Shape `tail-call` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: frame whose only work is a single tail `j`.
 */
void iosFmodf(void) {
    fmodf();
}
