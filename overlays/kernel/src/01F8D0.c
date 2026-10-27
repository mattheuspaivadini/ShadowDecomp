/* KERNEL.XFF @ 0x01F8D0 (12 B) - Sg2CtrlGetTickTime
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .bss+0x8f5c0 - returns that object as `int`.
 */
extern int D_kernel_bss_8F5C0;

int Sg2CtrlGetTickTime(void) {
    return D_kernel_bss_8F5C0;
}
