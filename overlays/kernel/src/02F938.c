/* KERNEL.XFF @ 0x02F938 (12 B) - Sg2ExPcmSetSignal
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .bss+0xac728.
 */
extern int D_kernel_bss_C728;

void Sg2ExPcmSetSignal(int a0) {
    D_kernel_bss_C728 = a0;
}
