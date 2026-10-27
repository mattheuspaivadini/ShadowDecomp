/* KERNEL.XFF @ 0x0156B0 (12 B) - getDrawScreenHeight
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .bss+0x2f01c - returns that object as `int`.
 */
extern int D_kernel_bss_2F01C;

int getDrawScreenHeight(void) {
    return D_kernel_bss_2F01C;
}
