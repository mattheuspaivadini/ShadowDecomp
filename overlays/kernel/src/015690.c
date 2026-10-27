/* KERNEL.XFF @ 0x015690 (12 B) - getDispScreenHeight
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .bss+0x2f014 - returns that object as `int`.
 */
extern int D_kernel_bss_2F014;

int getDispScreenHeight(void) {
    return D_kernel_bss_2F014;
}
