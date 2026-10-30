/* GAMECORE.XFF @ 0x00F640 (12 B) - backStageGetBossSaveArea
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .bss+0x80) - returns the object address.
 */
extern char D_kernel_bss_0080[];

int backStageGetBossSaveArea(void) {
    return (int)D_kernel_bss_0080;
}
