/* KERNEL.XFF @ 0x015680 (12 B) - getDispScreenWidth
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .bss+0x2f010 - returns that object as `int`.
 */
extern int D_kernel_bss_2F010;

int getDispScreenWidth(void) {
    return D_kernel_bss_2F010;
}
