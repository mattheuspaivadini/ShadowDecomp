/* GAMECORE.XFF @ 0x015420 (12 B) - getGameClearCntAdrs
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .bss+0xc74) - returns the object address.
 */
extern char D_kernel_bss_0C74[];

int getGameClearCntAdrs(void) {
    return (int)D_kernel_bss_0C74;
}
