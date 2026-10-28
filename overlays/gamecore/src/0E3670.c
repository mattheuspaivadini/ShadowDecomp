/* GAMECORE.XFF @ 0x0E3670 (12 B) - get_total_cameraman
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .bss+0x2c204 - returns that object as `int`.
 */
extern int D_kernel_bss_2C204;

int get_total_cameraman(void) {
    return D_kernel_bss_2C204;
}
