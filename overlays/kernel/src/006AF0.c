/* KERNEL.XFF @ 0x006AF0 (20 B) - iosResetKernel
 * Shape `tail-call` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: frame whose only work is a single tail `j`.
 */
void iosResetKernel(void) {
    LoaderSysResetSystem();
}
