/* GAMECORE.XFF @ 0x01D8A0 (12 B) - opflowChkLoadStart
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .bss+0x4ad0 - returns that object as `int`.
 */
extern int D_kernel_bss_4AD0;

int opflowChkLoadStart(void) {
    return D_kernel_bss_4AD0;
}
