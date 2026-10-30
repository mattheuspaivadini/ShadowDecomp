/* GAMECORE.XFF @ 0x11C540 (12 B) - SCRConditionResultHorse
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .bss+0x21f54 - returns that object as `int`.
 */
extern int D_kernel_bss_21F54;

int SCRConditionResultHorse(void) {
    return D_kernel_bss_21F54;
}
