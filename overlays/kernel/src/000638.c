/* KERNEL.XFF @ 0x000638 (48 B) - iosCdSetMode
 * Evidence: `bne $a0,$v1` (mode != 1) with the delay slot `addiu $a1,..,0x10`
 * hoisting the pointer slot (.bss+0x10) out of both arms, then the two arms
 * materialise one of two buffer addresses (`.bss+0x0` for mode 1, `.bss+0x8`
 * otherwise) and the common `sw $v0,0x0($a1)` stores it. That is
 * `ptr = (mode == 1) ? &bufA : &bufB;` with one target slot, not two.
 * UNCONFIRMED: the object names; `.data` is not typed here, so the two buffers
 * keep image labels.
 */
extern void *D_kernel_bss_0010;
extern char D_kernel_bss_0000;
extern char D_kernel_bss_0008;

void iosCdSetMode(int mode) {
    D_kernel_bss_0010 = (mode == 1) ? &D_kernel_bss_0000 : &D_kernel_bss_0008;
}
