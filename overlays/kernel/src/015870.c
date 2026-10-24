/* KERNEL.XFF @ 0x015870 (12 B) - getScreenOffsetX
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .bss+0x2f0bc) - returns the object address.
 */
extern char D_kernel_bss_F0BC[];

int getScreenOffsetX(void) {
    return (int)D_kernel_bss_F0BC;
}
