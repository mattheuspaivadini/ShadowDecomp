/* KERNEL.XFF @ 0x02F6D0 (12 B) - Sg2ExPcmOutputGetLipFrame
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .bss+0xabe38 - returns that object as `int`.
 */
extern int D_kernel_bss_ABE38;

int Sg2ExPcmOutputGetLipFrame(void) {
    return D_kernel_bss_ABE38;
}
