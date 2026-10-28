/* GAMECORE.XFF @ 0x015430 (12 B) - setGmaeClearCnt
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .bss+0xc74.
 */
extern int D_kernel_bss_0C74;

void setGmaeClearCnt(int a0) {
    D_kernel_bss_0C74 = a0;
}
