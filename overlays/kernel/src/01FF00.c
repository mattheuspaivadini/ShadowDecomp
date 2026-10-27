/* KERNEL.XFF @ 0x01FF00 (12 B) - Sg2ExStAdpcmStopMode
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .bss+0x8f5fc.
 */
extern int D_kernel_bss_F5FC;

void Sg2ExStAdpcmStopMode(int a0) {
    D_kernel_bss_F5FC = a0;
}
