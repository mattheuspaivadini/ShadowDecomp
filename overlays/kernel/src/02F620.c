/* KERNEL.XFF @ 0x02F620 (12 B) - Sg2ExPcmOutputSetOutputMode
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .bss+0xabe20.
 */
extern int D_kernel_bss_BE20;

void Sg2ExPcmOutputSetOutputMode(int a0) {
    D_kernel_bss_BE20 = a0;
}
