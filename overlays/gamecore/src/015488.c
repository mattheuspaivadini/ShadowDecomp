/* GAMECORE.XFF @ 0x015488 (12 B) - getSavedGameTime
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .bss+0xc6c - returns that object as `int`.
 */
extern int D_kernel_bss_0C6C;

int getSavedGameTime(void) {
    return D_kernel_bss_0C6C;
}
