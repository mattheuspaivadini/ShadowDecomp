/* KERNEL.XFF @ 0x005E08 (12 B) - iosPadEntryTickFunc
 * Evidence: HI16/LO16 pair against .data +0x268 and `sw $a0,%lo($v0)`:
 * stores the argument into one int-sized word. UNCONFIRMED name.
 */
extern int D_kernel_000268;

void iosPadEntryTickFunc(int fn) {
    D_kernel_000268 = fn;
}
