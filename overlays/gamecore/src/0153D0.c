/* GAMECORE.XFF @ 0x0153D0 (12 B) - setBossClearCnt
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .bss+0xc70.
 */
extern int D_kernel_bss_0C70;

void setBossClearCnt(int a0) {
    D_kernel_bss_0C70 = a0;
}
