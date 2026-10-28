/* GAMECORE.XFF @ 0x0153B0 (12 B) - getGameDataExistIcoData
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .bss+0xc78 - returns that object as `int`.
 */
extern int D_kernel_bss_0C78;

int getGameDataExistIcoData(void) {
    return D_kernel_bss_0C78;
}
