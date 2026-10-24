/* KERNEL.XFF @ 0x0158A0 (12 B) - getProgressiveMode
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .bss+0x2f0b4) - returns the object address.
 */
extern char D_kernel_bss_F0B4[];

int getProgressiveMode(void) {
    return (int)D_kernel_bss_F0B4;
}
