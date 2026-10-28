/* GAMECORE.XFF @ 0x019708 (12 B) - gStatGetOmakeStatAdrs
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .bss+0x49b0) - returns the object address.
 */
extern char D_kernel_bss_49B0[];

int gStatGetOmakeStatAdrs(void) {
    return (int)D_kernel_bss_49B0;
}
