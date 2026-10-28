/* GAMECORE.XFF @ 0x015410 (12 B) - getGameClearCnt
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .bss+0xc74 - returns that object as `int`.
 */
extern int D_kernel_bss_0C74;

int getGameClearCnt(void) {
    return D_kernel_bss_0C74;
}
