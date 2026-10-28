/* GAMECORE.XFF @ 0x0153C0 (12 B) - getGameDataExistIcoDataAdrs
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .bss+0xc78) - returns the object address.
 */
extern char D_kernel_bss_0C78[];

int getGameDataExistIcoDataAdrs(void) {
    return (int)D_kernel_bss_0C78;
}
