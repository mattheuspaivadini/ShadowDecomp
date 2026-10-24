/* KERNEL.XFF @ 0x02C4E0 (12 B) - Sg2SmfpSetSignal
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .bss+0xaac88.
 */
extern int D_kernel_bss_AC88;

void Sg2SmfpSetSignal(int a0) {
    D_kernel_bss_AC88 = a0;
}
