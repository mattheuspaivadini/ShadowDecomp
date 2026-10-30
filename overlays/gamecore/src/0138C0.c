/* GAMECORE.XFF @ 0x0138C0 (12 B) - endingflowTickAdpcmSeq
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .bss+0x344.
 */
extern int D_kernel_bss_0344;

void endingflowTickAdpcmSeq(int a0) {
    D_kernel_bss_0344 = a0;
}
