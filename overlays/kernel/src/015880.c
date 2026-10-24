/* KERNEL.XFF @ 0x015880 (12 B) - getScreenOffsetY
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .bss+0x2f0c0) - returns the object address.
 */
extern char D_kernel_bss_F0C0[];

int getScreenOffsetY(void) {
    return (int)D_kernel_bss_F0C0;
}
