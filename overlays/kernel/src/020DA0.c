/* KERNEL.XFF @ 0x020DA0 (12 B) - Sg2ExStAdpcmSetSignal
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .bss+0x8f6c0.
 */
extern int D_kernel_bss_F6C0;

void Sg2ExStAdpcmSetSignal(int a0) {
    D_kernel_bss_F6C0 = a0;
}
