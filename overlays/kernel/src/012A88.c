/* KERNEL.XFF @ 0x012A88 (12 B) - iosGetDCGroup
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .bss+0x2eac8) - returns the object address.
 */
extern char D_kernel_bss_EAC8[];

int iosGetDCGroup(void) {
    return (int)D_kernel_bss_EAC8;
}
