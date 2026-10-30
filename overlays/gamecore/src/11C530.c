/* GAMECORE.XFF @ 0x11C530 (12 B) - SCRConditionResultBoss
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .bss+0x21f50 - returns that object as `int`.
 */
extern int D_kernel_bss_21F50;

int SCRConditionResultBoss(void) {
    return D_kernel_bss_21F50;
}
